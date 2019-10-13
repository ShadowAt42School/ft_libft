/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:36:23 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/13 02:15:16 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

void			build_flags(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (fmt->decorators.is_blank_space && INTSIGN(fmt->specifier))
		*(*res + str_start) = ' ';
	if ((fmt->decorators.is_force_sign || fmt->intval.llin < 0) &&
												INTSIGN(fmt->specifier))
		*(*res + str_start) = fmt->intval.llin < 0 ? '-' : '+';
	if (fmt->decorators.is_preceed_ox && ((INTUSIGNS(fmt->specifier) &&
						(fmt->intval.ullin != 0 || fmt->specifier == 'o')) ||
						POINTER(fmt->specifier)))
	{
		if (fmt->specifier == 'o' && fmt->len.processed > fmt->len.value)
			return ;
		ft_memcpy(*res + str_start,
			FLHSSTR(fmt->specifier),
			FLHSLEN(fmt->specifier));
	}
}

void			build_precision(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (INTSPEC(fmt->specifier) && fmt->precision != 0)
		ft_memset(*res + str_start, '0', fmt->precision);
}

void			build_specifier(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (INTSPEC(fmt->specifier))
	{
		if (fmt->decorators.is_precision && fmt->precision == 0 &&
							(fmt->intval.ullin == 0 && fmt->intval.llin == 0))
			return ;
		ft_memcpy(
			*res + str_start,
			fmt->intval.buffer[0] == '-' ?
				fmt->intval.buffer + 1 : fmt->intval.buffer,
			fmt->len.value);
		if (!fmt->decorators.is_capital)
			ft_str_tolower(*res + str_start);
	}
	else if (STRING(fmt->specifier))
		ft_memcpy(*res + str_start, fmt->value.str, fmt->len.processed);
	else if (CHART(fmt->specifier))
		*(*res + str_start) = fmt->value.schar;
	else
		*(*res + str_start) = fmt->specifier;
}
