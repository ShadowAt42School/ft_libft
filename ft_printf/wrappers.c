/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:40:53 by maghayev          #+#    #+#             */
/*   Updated: 2019/09/29 22:30:14 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

t_result	*setup(const char *format)
{
	t_result	*result;

	result = ft_memalloc(sizeof(t_result));
	result->format = format;
	result->lenght_format = ft_strlen(format);
	return (result);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_result	*result;

	result = setup(format);
	va_start(ap, format);
	ft_engine(&ap, result);
	va_end(ap);
	return (result->length_print);
}
