/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:50:16 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/09 23:38:55 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

void	parse_flags(const char **format, t_formater *formater)
{
	while (ISFLAG(**format))
	{
		if (**format == '+')
			formater->flags = formater->flags | 1;
		else if (**format == '-')
			formater->flags = formater->flags | 2;
		else if (**format == ' ' && !ISFLAGSP(formater->flags))
			formater->flags = formater->flags | 4;
		else if (**format == '#')
			formater->flags = formater->flags | 8;
		else if (**format == '0' && !ISFLAGSM(formater->flags))
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
	char			is_variable;
	static t_bool	call_times;

	is_variable = FALSE;
	if (call_times == 2)
		call_times = 0;
	length = 0;
	if (**format == '.' && call_times == 1 &&
									(formater->decorators.is_precision = TRUE))
		(*format)++;
	if (**format == '*')
	{
		(*format)++;
		length = va_arg(*ap, unsigned int);
		is_variable = TRUE;
	}
	if (formater->decorators.is_precision && call_times == 1)
		formater->precision = is_variable ? length : ft_atoi(*format);
	if (call_times == 0 && !formater->decorators.is_precision)
		formater->width = is_variable ? length : ft_atoi(*format);
	if (!is_variable)
		ft_strnumlen_inplace(format);
	call_times++;
}

void	parse_length(const char **format, t_formater *formater)
{
	while (ISLENGTH(**format))
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
	formater->specifier = **format;
	if (ISFLOAT(**format))
	{
		if (formater->length == LF)
			formater->value.ldnumber = va_arg(*ap, long double);
		else
			formater->value.dnumber = va_arg(*ap, double);
	}
	else
		formater->value.pspec = va_arg(*ap, void*);
	(*format)++;
}

void	build_decorators(t_formater *fmt)
{
	if (IS_UPPER(fmt->specifier))
	{
		if (fmt->length == NO && fmt->length != LF && DOUL(fmt->specifier))
			fmt->length = L;
		fmt->decorators.is_capital = TRUE;
		fmt->specifier = ft_tolower(fmt->specifier);
	}
	if (BASE10(fmt->specifier) &&
					(ISFLAGSP(fmt->flags)))
		fmt->decorators.is_force_sign = TRUE;
	if (ISFLAGSM(fmt->flags))
		fmt->decorators.is_left_justify = TRUE;
	if (BASE10(fmt->specifier) && ISFLAGSPC(fmt->flags))
		fmt->decorators.is_blank_space = TRUE;
	if (ISFLAGHS(fmt->flags) && (ISFLOAT(fmt->specifier) ||
												UOCTHEX(fmt->specifier)))
	{
		fmt->decorators.is_preceed_ox = TRUE;
		fmt->decorators.is_force_decimal = TRUE;
	}
	if (ISFLAGZERO(fmt->flags) ||
		(INT_SPEC(fmt->specifier) && fmt->decorators.is_precision))
		fmt->decorators.is_pad_zeros = TRUE;
	if (fmt->specifier == 'p' && (fmt->length = 4))
		fmt->decorators.is_preceed_ox = TRUE;
}
