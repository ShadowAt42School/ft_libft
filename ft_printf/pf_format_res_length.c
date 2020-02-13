/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_res_length.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:45:54 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 22:26:11 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int			specifier_conv_length(t_formater *fmt)
{
	if (pf_is_sint(fmt->specifier))
		return (ft_itoa_base((char*)fmt->intval.buffer,
							&fmt->intval.llin, pf_base(fmt->specifier), TRUE));
	else if (pf_is_uint(fmt->specifier) || pf_is_uints(fmt->specifier))
		return (ft_itoa_base((char*)fmt->intval.buffer,
						&fmt->intval.ullin, pf_base(fmt->specifier), FALSE));
	else if (pf_is_float(fmt->specifier) && fmt->length != LF)
		return (ft_dtos(fmt->value.dnumber,
			fmt->decorators.is_precision ? fmt->precision : -1,
			fmt->decorators.is_preceed_ox, (char*)fmt->intval.buffer));
	else if (pf_is_float(fmt->specifier) && fmt->length == LF)
		return (ft_dtos(fmt->value.ldnumber,
			fmt->decorators.is_precision ? fmt->precision : -1,
			fmt->decorators.is_preceed_ox, (char*)fmt->intval.buffer));
	else if (pf_is_str(fmt->specifier))
		return (ft_strlen(fmt->value.str));
	else if (pf_is_char(fmt->specifier) || !pf_is_spec(fmt->specifier))
		return (1);
	return (0);
}

static unsigned int			specifier_length(t_formater *fmt)
{
	long long int			llin;
	unsigned long long int	ullin;

	if (fmt->length == HH && (ullin = (t_ullint)fmt->value.uchar))
		llin = (t_llint)fmt->value.schar;
	else if (fmt->length == H && (ullin = (t_ullint)fmt->value.ushintd))
		llin = (t_llint)fmt->value.shint;
	else if (fmt->length == L && (ullin = (t_ullint)fmt->value.ulint))
		llin = (t_llint)fmt->value.lint;
	else if (fmt->length == LL && (ullin = (t_ullint)fmt->value.ullint))
		llin = (t_llint)fmt->value.llint;
	else if (fmt->length == J && (ullin = (t_ullint)fmt->value.uintmax))
		llin = (t_llint)fmt->value.intmax;
	else if (fmt->length == Z && (ullin = (t_ullint)fmt->value.sizet))
		llin = (t_llint)fmt->value.sizet;
	else if (fmt->length == T && (ullin = (t_ullint)fmt->value.ptrdiff))
		llin = (t_llint)fmt->value.ptrdiff;
	else
	{
		ullin = (t_ullint)fmt->value.uintd;
		llin = (t_llint)fmt->value.intd;
	}
	fmt->intval.llin = llin;
	fmt->intval.ullin = ullin;
	return (specifier_conv_length(fmt));
}

static void					flags_length(
	t_formater *fmt
)
{
	if (fmt->decorators.is_blank_space || fmt->decorators.is_force_sign ||
						(fmt->intval.llin < 0 && pf_is_sint(fmt->specifier)))
		fmt->len.aux = 1;
	if (pf_is_float(fmt->specifier) &&
							((fmt->length != LF && fmt->value.dnumber < 0) ||
								(fmt->length == LF && fmt->value.ldnumber < 0)))
		fmt->len.aux = 1;
	if ((fmt->decorators.is_preceed_ox &&
						(pf_is_uints(fmt->specifier) && fmt->intval.ullin != 0))
											|| pf_is_pointer(fmt->specifier))
	{
		if (fmt->specifier == 'o' && fmt->len.processed > fmt->len.value &&
								!(fmt->len.aux -= pf_flhslen(fmt->specifier)))
			return ;
		fmt->len.aux = pf_flhslen(fmt->specifier);
	}
}

/*
**	TODO: Add float length function
*/

static void					length_length(
	t_formater *fmt
)
{
	int	length;

	length = fmt->len.value;
	if (pf_is_int(fmt->specifier))
	{
		if (fmt->decorators.is_precision)
			length = length < fmt->precision ? fmt->precision : length;
		else if (fmt->decorators.is_precision && fmt->precision == 0 &&
							(fmt->intval.ullin == 0 && fmt->intval.llin == 0))
			length = 0;
		else if (fmt->width > 0 && fmt->decorators.is_pad_zeros &&
					!fmt->decorators.is_ljustify && length < fmt->width)
			length = fmt->width - fmt->len.aux;
	}
	else
	{
		if (fmt->specifier == 's' && fmt->len.value > 0)
			length = fmt->decorators.is_precision && fmt->precision < length ?
													fmt->precision : length;
		else if (fmt->specifier == 'c' || !pf_is_spec(fmt->specifier))
			length = 1;
		fmt->len.value = length == 1 ? 1 : length;
	}
	fmt->len.processed = length;
}

void						pf_prepare_length(
	unsigned int *current_length,
	t_formater *fmt
)
{
	fmt->len.value = specifier_length(fmt);
	flags_length(fmt);
	if (fmt->intval.llin == 0 && fmt->intval.ullin == 0 &&
		fmt->decorators.is_precision && fmt->precision == 0 &&
		!(fmt->specifier == 'o' && fmt->decorators.is_preceed_ox)
		&& pf_is_int(fmt->specifier) && (fmt->len.value = 0))
		return ;
	length_length(fmt);
	flags_length(fmt);
	if (fmt->width > 0 && fmt->width > (fmt->len.aux + fmt->len.processed))
		*current_length = fmt->width;
	else
		*current_length = fmt->len.aux + fmt->len.processed;
}
