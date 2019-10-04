/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_res_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:45:54 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/03 23:13:31 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

void			flags_length(unsigned int *current_length, t_formater *fmt)
{
	unsigned int length;

	length = 0;
	length += fmt->decorators.is_blank_space ? 1 : 0;
	length += fmt->decorators.is_force_sign ? 1 : 0;
	length += fmt->decorators.is_preceed_ox ? 1 : 0;
	if ((fmt->decorators.is_precision && fmt->precision >= fmt->width) ||
		*current_length > fmt->width)
		*current_length += length;
	fmt->value_length += length;
}

/*
**	TODO: Add float length function
*/

void			length_length(unsigned int *current_length, t_formater *form)
{
	unsigned int	length;

	length = 0;
	if (INT_SPEC(form->specifier))
	{
		length = numspecifier_length(form, !SIGNPOSSIBLE(form->specifier));
		if (form->decorators.is_precision)
			length = length < form->precision ? form->precision : length;
	}
	if (form->specifier == 's')
		length = form->decorators.is_precision ?
								form->precision : ft_strlen(form->value.str);
	if (form->specifier == 'c')
		length = 1;
	form->value_length = length;
	*current_length = *current_length < length ? length : *current_length;
}

unsigned int	numspecifier_length(t_formater *fmt, t_bool is_u)
{
	if (fmt->length == HH)
		return (ft_numlen(!is_u ? fmt->value.schar : fmt->value.uchar));
	else if (fmt->length == H)
		return (ft_numlen(!is_u ? fmt->value.shint : fmt->value.ushintd));
	else if (fmt->length == L)
		return (ft_numlen(!is_u ? fmt->value.lint : fmt->value.ulint));
	else if (fmt->length == LL)
		return (ft_numlen(!is_u ? fmt->value.llint : fmt->value.ullint));
	else if (fmt->length == J)
		return (ft_numlen(!is_u ? fmt->value.intmax : fmt->value.uintmax));
	else if (fmt->length == Z)
		return (ft_numlen(fmt->value.sizet));
	else if (fmt->length == T)
		return (ft_numlen(fmt->value.ptrdiff));
	return (ft_numlen(!is_u ? fmt->value.intd : fmt->value.intd));
}
