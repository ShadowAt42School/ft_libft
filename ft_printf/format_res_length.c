/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_res_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:45:54 by maghayev          #+#    #+#             */
/*   Updated: 2019/11/10 23:54:55 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

static unsigned int			specifier_conv_length(t_formater *fmt)
{
	if (INTSIGN(fmt->specifier))
		return (ft_itoa_base((char*)fmt->intval.buffer,
			&fmt->intval.llin,
			BASE(fmt->specifier),
			INTSIGN(fmt->specifier)));
	else if (INTUSIGN(fmt->specifier) || INTUSIGNS(fmt->specifier))
		return (ft_itoa_base((char*)fmt->intval.buffer,
			&fmt->intval.ullin,
			BASE(fmt->specifier),
			FALSE));
	else if (STRING(fmt->specifier))
		return (ft_strlen(fmt->value.str));
	else if (CHART(fmt->specifier) || !ISSPECIF(fmt->specifier))
		return (1);
	return (0);
}

static unsigned int			specifier_length(t_formater *fmt)
{
	long long int			llin;
	unsigned long long int	ullin;

	if (fmt->length == HH && (ullin = ULLINTD(fmt->value.uchar)))
		llin = LLINTD(fmt->value.schar);
	else if (fmt->length == H && (ullin = ULLINTD(fmt->value.ushintd)))
		llin = LLINTD(fmt->value.shint);
	else if (fmt->length == L && (ullin = ULLINTD(fmt->value.ulint)))
		llin = LLINTD(fmt->value.lint);
	else if (fmt->length == LL && (ullin = ULLINTD(fmt->value.ullint)))
		llin = LLINTD(fmt->value.llint);
	else if (fmt->length == J && (ullin = ULLINTD(fmt->value.intmax)))
		llin = LLINTD(fmt->value.intmax);
	else if (fmt->length == Z && (ullin = ULLINTD(fmt->value.sizet)))
		llin = LLINTD(fmt->value.sizet);
	else if (fmt->length == T && (ullin = ULLINTD(fmt->value.intd)))
		llin = LLINTD(fmt->value.ptrdiff);
	else
	{
		ullin = ULLINTD(fmt->value.uintd);
		llin = LLINTD(fmt->value.intd);
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
							(fmt->intval.llin < 0 && INTSIGN(fmt->specifier)))
		fmt->len.aux = 1;
	if ((fmt->decorators.is_preceed_ox && fmt->intval.ullin != 0) ||
														POINTER(fmt->specifier))
	{
		if (fmt->specifier == 'o' && fmt->len.processed > fmt->len.value &&
									!(fmt->len.aux -= FLHSLEN(fmt->specifier)))
			return ;
		fmt->len.aux = FLHSLEN(fmt->specifier);
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
	if (INTSPEC(fmt->specifier))
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
		else if (fmt->specifier == 'c' || !ISSPECIF(fmt->specifier))
			length = 1;
		fmt->len.value = length == 1 ? 1 : length;
	}
	fmt->len.processed = length;
}

void						prepare_length(
	unsigned int *current_length,
	t_formater *fmt
)
{
	fmt->len.value = specifier_length(fmt);
	flags_length(fmt);
	if (fmt->intval.llin == 0 && fmt->intval.ullin == 0 &&
		fmt->decorators.is_precision && fmt->precision == 0 &&
		!(fmt->specifier == 'o' && fmt->decorators.is_preceed_ox)
		&& (fmt->len.value = 0))
		return ;
	length_length(fmt);
	flags_length(fmt);
	if (fmt->width > 0 && fmt->width > (fmt->len.aux + fmt->len.processed))
		*current_length = fmt->width;
	else
		*current_length = fmt->len.aux + fmt->len.processed;
}
