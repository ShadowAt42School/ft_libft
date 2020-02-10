/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:36:23 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 23:02:40 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			build_flags(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (fmt->decorators.is_blank_space &&
						(is_sint(fmt->specifier) || is_float(fmt->specifier)))
		*(*res + str_start) = ' ';
	if ((fmt->decorators.is_force_sign || fmt->intval.buffer[0] == '-') &&
						(is_sint(fmt->specifier) || is_float(fmt->specifier)))
		*(*res + str_start) = fmt->intval.buffer[0] == '-' ? '-' : '+';
	if (fmt->decorators.is_preceed_ox && ((is_uints(fmt->specifier) &&
						(fmt->intval.ullin != 0 || fmt->specifier == 'o')) ||
						is_pointer(fmt->specifier)))
	{
		if (fmt->specifier == 'o' && fmt->len.processed > fmt->len.value)
			return ;
		ft_memcpy(*res + str_start,
			flhsstr(fmt->specifier),
			flhslen(fmt->specifier));
	}
}

void			build_precision(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (is_int(fmt->specifier) && fmt->precision != 0)
		ft_memset(*res + str_start, '0', fmt->precision);
}

void			build_specifier(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (!fmt->specifier)
		return ;
	if (is_int(fmt->specifier))
	{
		if (fmt->decorators.is_precision && fmt->precision == 0 &&
							(fmt->intval.ullin == 0 && fmt->intval.llin == 0))
			return ;
		ft_memcpy(
			*res + str_start,
			fmt->intval.buffer[0] == '-' ?
			fmt->intval.buffer + 1 : fmt->intval.buffer, fmt->len.value);
		if (!fmt->decorators.is_capital)
			ft_strlower(*res + str_start);
	}
	else if (is_float(fmt->specifier))
		ft_memcpy(*res + str_start,
			fmt->intval.buffer[0] == '-' ?
			fmt->intval.buffer + 1 : fmt->intval.buffer, fmt->len.processed);
	else if (is_str(fmt->specifier))
		ft_memcpy(*res + str_start, fmt->value.str, fmt->len.processed);
	else if (is_char(fmt->specifier))
		*(*res + str_start) = fmt->value.schar;
	else
		*(*res + str_start) = fmt->specifier;
}
