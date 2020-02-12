/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:50:16 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 22:36:43 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_parse_flags(
	const char **format,
	t_formater *formater,
	void *ap
)
{
	while (pf_is_flag(**format) && ap)
	{
		if (**format == '+')
			formater->flags = formater->flags | 1;
		else if (**format == '-')
			formater->flags = formater->flags | 2;
		else if (**format == ' ' && !pf_is_fsp(formater->flags))
			formater->flags = formater->flags | 4;
		else if (**format == '#')
			formater->flags = formater->flags | 8;
		else if (**format == '0' && !pf_is_fsm(formater->flags))
			formater->flags = formater->flags | 16;
		(*format)++;
	}
}

void	pf_parse_width_precision(
	const char **format,
	t_formater *formater,
	va_list *ap
)
{
	int				length;
	t_bool			is_variable;
	t_bool			is_pres;

	is_variable = FALSE;
	is_pres = FALSE;
	length = 0;
	if (**format == '.' && (formater->decorators.is_precision = TRUE) &&
															(is_pres = TRUE))
		(*format)++;
	if (**format == '*')
	{
		(*format)++;
		length = va_arg(*ap, int);
		if (length < 0 && ((!is_pres && (formater->flags |= 2)) ||
					(is_pres && !(formater->decorators.is_precision = FALSE))))
			length *= is_pres ? 0 : -1;
		is_variable = TRUE;
	}
	if (is_pres)
		formater->precision = is_variable ? length : ft_atoi(*format);
	else
		formater->width = is_variable ? length : ft_atoi(*format);
	if (!is_variable)
		ft_strnumlen_inplace(format);
}

void	pf_parse_length(
	const char **format,
	t_formater *formater,
	void *ap
)
{
	while (pf_is_len(**format) && ap)
	{
		if (**format == 'h' && formater->length < HH)
			formater->length = *(*format + 1) == 'h' ? HH : H;
		else if (**format == 'l' && formater->length < LL)
			formater->length = *(*format + 1) == 'l' ? LL : L;
		else if (**format == 'j' && formater->length < J)
			formater->length = J;
		else if (**format == 'z' && formater->length < Z)
			formater->length = Z;
		else if (**format == 't' && formater->length < T)
			formater->length = T;
		else if (**format == 'L' && formater->length < LF)
			formater->length = LF;
		(*format) += formater->length == HH || formater->length == LL ? 2 : 1;
	}
}

void	pf_parse_specifier(
	const char **format,
	t_formater *formater,
	va_list *ap
)
{
	if (!**format)
		return ;
	formater->specifier = **format;
	if (pf_is_spec(**format))
	{
		if (pf_is_float(**format))
		{
			if (formater->length == LF)
				formater->value.ldnumber = va_arg(*ap, long double);
			else
				formater->value.dnumber = va_arg(*ap, double);
		}
		else
			formater->value.pspec = va_arg(*ap, void*);
		if (!formater->value.pspec && pf_is_str(formater->specifier))
			formater->value.pspec = (void *)"(null)";
	}
	(*format)++;
}

void	pf_build_decorators(t_formater *fmt)
{
	if (ft_isupper(fmt->specifier))
	{
		if (fmt->length < L && fmt->length != LF && pf_caplen(fmt->specifier))
			fmt->length = L;
		fmt->decorators.is_capital = TRUE;
	}
	fmt->decorators.is_force_sign = pf_is_fsp(fmt->flags) &&
					(pf_is_sint(fmt->specifier) || pf_is_float(fmt->specifier));
	fmt->decorators.is_ljustify = pf_is_fsm(fmt->flags);
	fmt->decorators.is_blank_space = pf_is_fspc(fmt->flags) &&
					(pf_is_sint(fmt->specifier) || pf_is_float(fmt->specifier));
	fmt->decorators.is_preceed_ox = pf_is_fhs(fmt->flags) &&
				(pf_is_uints(fmt->specifier) || pf_is_float(fmt->specifier));
	fmt->decorators.is_force_decimal = (pf_is_fhs(fmt->flags) &&
												pf_is_float(fmt->specifier));
	if ((pf_is_fzero(fmt->flags) && !pf_is_fsm(fmt->flags)) ||
		(pf_is_int(fmt->specifier) && fmt->decorators.is_precision))
		fmt->decorators.is_pad_zeros = TRUE;
	if (fmt->specifier == 'p' && (fmt->length = 4))
		fmt->decorators.is_preceed_ox = TRUE;
}
