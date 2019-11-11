/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:50:16 by maghayev          #+#    #+#             */
/*   Updated: 2019/11/11 00:09:26 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

void	parse_flags(
	const char **format,
	t_formater *formater,
	void *ap
)
{
	while (ISFLAG(**format) && ap)
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
	while (ISLENGTH(**format) && ap)
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
	if (ISSPECIF(**format))
	{
		if (FLOAT(**format))
		{
			if (formater->length == LF)
				formater->value.ldnumber = va_arg(*ap, long double);
			else
				formater->value.dnumber = va_arg(*ap, double);
		}
		else
			formater->value.pspec = va_arg(*ap, void*);
		if (!formater->value.pspec && STRING(formater->specifier))
			formater->value.pspec = (void *)"(null)";
	}
	(*format)++;
}

void	build_decorators(t_formater *fmt)
{
	if (IS_UPPER(fmt->specifier))
	{
		if (fmt->length < L && fmt->length != LF && CAPLEN(fmt->specifier))
			fmt->length = L;
		fmt->decorators.is_capital = TRUE;
	}
	fmt->decorators.is_force_sign = ISFLAGSP(fmt->flags) &&
														INTSIGN(fmt->specifier);
	fmt->decorators.is_ljustify = ISFLAGSM(fmt->flags);
	fmt->decorators.is_blank_space = ISFLAGSPC(fmt->flags) &&
														INTSIGN(fmt->specifier);
	fmt->decorators.is_preceed_ox = (ISFLAGHS(fmt->flags) &&
													INTUSIGNS(fmt->specifier));
	fmt->decorators.is_force_decimal = (ISFLAGHS(fmt->flags) &&
														FLOAT(fmt->specifier));
	if ((ISFLAGZERO(fmt->flags) && !ISFLAGSM(fmt->flags)) ||
		(INTSPEC(fmt->specifier) && fmt->decorators.is_precision))
		fmt->decorators.is_pad_zeros = TRUE;
	if (fmt->specifier == 'p' && (fmt->length = 4))
		fmt->decorators.is_preceed_ox = TRUE;
	if (!fmt->decorators.is_precision && FLOAT(fmt->specifier) &&
														(fmt->precision = 6))
		fmt->decorators.is_precision = TRUE;
}
