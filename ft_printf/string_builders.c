/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:36:23 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/08 23:30:19 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

void			build_flags(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (fmt->decorators.is_blank_space && SIGNPOSSIBLE(fmt->specifier))
		*(*res + str_start) = ' ';
	if ((fmt->decorators.is_force_sign || fmt->integer_values.llin < 0) &&
												SIGNPOSSIBLE(fmt->specifier))
		*(*res + str_start) = fmt->integer_values.llin < 0 ? '-' : '+';
	if (fmt->decorators.is_preceed_ox)
		ft_memcpy(*res + str_start,
			fmt->integer_values.ullin != 0 ?
					STR_OX(fmt->decorators.is_capital) : (*res + str_start),
			LEN_OX(fmt->specifier));
}

void			build_precision(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (INT_SPEC(fmt->specifier) && !((fmt->integer_values.llin != 0 ||
						fmt->integer_values.ullin != 0) && fmt->precision == 0))
		ft_memset(*res + str_start, '0', fmt->precision);
	else if (fmt->specifier == 's')
		ft_memset(*res + str_start, ' ', fmt->processed_length);
}

void			build_specifier(
	char **res,
	t_formater *fmt,
	unsigned int str_start
)
{
	if (INT_SPEC(fmt->specifier))
	{
		ft_memcpy(
			*res + str_start,
			fmt->integer_values.buffer[0] == '-' ?
				fmt->integer_values.buffer + 1 : fmt->integer_values.buffer,
			fmt->value_length);
		if (!fmt->decorators.is_capital)
			ft_str_tolower(*res + str_start);
	}
	else if (fmt->specifier == 's')
		ft_memcpy(*res + str_start, fmt->value.str, fmt->processed_length);
	else if (fmt->specifier == 'c')
		*(*res + str_start) = fmt->value.schar;
	else
		*(*res + str_start) = fmt->specifier;
}
