/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:50:16 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 22:57:17 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

void	parse_flags(
	const char **format,
	t_formater *formater,
	void *ap
)
{
	while (is_flag(**format) && ap)
	{
		if (**format == '+')
			formater->flags = formater->flags | 1;
		else if (**format == '-')
			formater->flags = formater->flags | 2;
		else if (**format == ' ' && !is_fsp(formater->flags))
			formater->flags = formater->flags | 4;
		else if (**format == '#')
			formater->flags = formater->flags | 8;
		else if (**format == '0' && !is_fsm(formater->flags))
			formater->flags = formater->flags | 16;
		(*format)++;
	}
}

void	parse_width_precision(
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

void	parse_length(
	const char **format,
	t_formater *formater,
	void *ap
)
{
	while (is_len(**format) && ap)
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

void	parse_specifier(
	const char **format,
	t_formater *formater,
	va_list *ap
)
{
	if (!**format)
		return ;
	formater->specifier = **format;
	if (is_spec(**format))
	{
		if (is_float(**format))
		{
			if (formater->length == LF)
				formater->value.ldnumber = va_arg(*ap, long double);
			else
				formater->value.dnumber = va_arg(*ap, double);
		}
		else
			formater->value.pspec = va_arg(*ap, void*);
		if (!formater->value.pspec && is_str(formater->specifier))
			formater->value.pspec = (void *)"(null)";
	}
	(*format)++;
}

void	build_decorators(t_formater *fmt)
{
	if (ft_isupper(fmt->specifier))
	{
		if (fmt->length < L && fmt->length != LF && caplen(fmt->specifier))
			fmt->length = L;
		fmt->decorators.is_capital = TRUE;
	}
	fmt->decorators.is_force_sign = is_fsp(fmt->flags) &&
						(is_sint(fmt->specifier) || is_float(fmt->specifier));
	fmt->decorators.is_ljustify = is_fsm(fmt->flags);
	fmt->decorators.is_blank_space = is_fspc(fmt->flags) &&
						(is_sint(fmt->specifier) || is_float(fmt->specifier));
	fmt->decorators.is_preceed_ox = is_fhs(fmt->flags) &&
						(is_uints(fmt->specifier) || is_float(fmt->specifier));
	fmt->decorators.is_force_decimal = (is_fhs(fmt->flags) &&
													is_float(fmt->specifier));
	if ((is_fzero(fmt->flags) && !is_fsm(fmt->flags)) ||
		(is_int(fmt->specifier) && fmt->decorators.is_precision))
		fmt->decorators.is_pad_zeros = TRUE;
	if (fmt->specifier == 'p' && (fmt->length = 4))
		fmt->decorators.is_preceed_ox = TRUE;
}
