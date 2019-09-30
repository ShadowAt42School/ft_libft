/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:50:16 by maghayev          #+#    #+#             */
/*   Updated: 2019/09/29 22:02:33 by maghayev         ###   ########.fr       */
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
	int		length;
	char	is_variable;
	char	is_precision;

	is_variable = FALSE;
	is_precision = FALSE;
	length = 0;
	if (**format == '.')
	{
		(*format)++;
		is_precision = TRUE;
	}
	if (**format == '*')
	{
		(*format)++;
		length = va_arg(*ap, unsigned int);
		is_variable = TRUE;
	}
	if (is_precision)
		formater->precision = is_variable ? length : ft_atoi(*format);
	else
		formater->width = is_variable ? length : ft_atoi(*format);
	if (!is_variable)
		ft_strnumlen_inplace(format);
}

void	parse_length()
{

}

void	parse_specifier()
{

}
