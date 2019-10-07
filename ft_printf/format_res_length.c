/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_res_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:45:54 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/06 23:33:17 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"
#include <stdio.h>

static unsigned int		specifier_conv_length(t_formater *fmt)
{
	if (fmt->decorators.is_precision && fmt->precision == 0)
		if (fmt->integer_values.llin == 0 && fmt->integer_values.llin == 0)
			return (0);
	return (ft_itoa_base((char*)fmt->integer_values.buffer,
		SIGNPOSSIBLE(fmt->specifier) ?
		&fmt->integer_values.llin : &fmt->integer_values.llin,
		BASE(fmt->specifier),
		SIGNPOSSIBLE(fmt->specifier)));
}

static unsigned int		numspecifier_length(t_formater *fmt)
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
	fmt->integer_values.llin = llin;
	fmt->integer_values.ullin = ullin;
	return (specifier_conv_length(fmt));
}

void					flags_length(
	unsigned int *current_length,
	t_formater *fmt
)
{
	unsigned int length;

	length = 0;
	if (fmt->decorators.is_blank_space &&
									(fmt->aux_length += 1))
		length += 1;
	if (fmt->decorators.is_force_sign &&
									(fmt->aux_length += 1))
		length += 1;
	if (fmt->decorators.is_preceed_ox && fmt->integer_values.ullin != 0 &&
									(fmt->aux_length += LEN_OX(fmt->specifier)))
		length += fmt->aux_length;
	if ((fmt->decorators.is_precision && fmt->precision >= fmt->width) ||
		*current_length > fmt->width)
		*current_length += length;
	fmt->processed_length += length;
}

/*
**	TODO: Add float length function
*/

void					length_length(
	unsigned int *current_length,
	t_formater *form
)
{
	unsigned int	length;

	length = 0;
	if (INT_SPEC(form->specifier))
	{
		length = numspecifier_length(form);
		form->value_length = length;
		if (form->decorators.is_precision)
			length = length < form->precision ? form->precision : length;
	}
	if (form->specifier == 's')
	{
		length = form->decorators.is_precision ?
								form->precision : ft_strlen(form->value.str);
		form->value_length = length;
	}
	if (form->specifier == 'c' && (form->value_length = 1))
		length = 1;
	form->processed_length = length;
	*current_length = *current_length < length ? length : *current_length;
}
