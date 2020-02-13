/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string_builders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:36:23 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 22:26:38 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_build_flags(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (fmt->decorators.is_blank_space &&
					(pf_is_sint(fmt->specifier) || pf_is_float(fmt->specifier)))
		*(*res + str_start) = ' ';
	if ((fmt->decorators.is_force_sign || fmt->intval.buffer[0] == '-') &&
					(pf_is_sint(fmt->specifier) || pf_is_float(fmt->specifier)))
		*(*res + str_start) = fmt->intval.buffer[0] == '-' ? '-' : '+';
	if (fmt->decorators.is_preceed_ox && ((pf_is_uints(fmt->specifier) &&
						(fmt->intval.ullin != 0 || fmt->specifier == 'o')) ||
						pf_is_pointer(fmt->specifier)))
	{
		if (fmt->specifier == 'o' && fmt->len.processed > fmt->len.value)
			return ;
		ft_memcpy(*res + str_start,
			pf_flhsstr(fmt->specifier),
			pf_flhslen(fmt->specifier));
	}
}

void			pf_build_precision(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (pf_is_int(fmt->specifier) && fmt->precision != 0)
		ft_memset(*res + str_start, '0', fmt->precision);
}

void			pf_build_specifier(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (!fmt->specifier)
		return ;
	if (pf_is_int(fmt->specifier))
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
	else if (pf_is_float(fmt->specifier))
		ft_memcpy(*res + str_start,
			fmt->intval.buffer[0] == '-' ?
			fmt->intval.buffer + 1 : fmt->intval.buffer, fmt->len.processed);
	else if (pf_is_str(fmt->specifier))
		ft_memcpy(*res + str_start, fmt->value.str, fmt->len.processed);
	else if (pf_is_char(fmt->specifier))
		*(*res + str_start) = fmt->value.schar;
	else
		*(*res + str_start) = fmt->specifier;
}
