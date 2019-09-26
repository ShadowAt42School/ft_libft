/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:40:53 by maghayev          #+#    #+#             */
/*   Updated: 2019/09/25 22:16:01 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

t_item	*setup(const char *format)
{
	t_item	*item;

	item = ft_memalloc(sizeof(t_item));
	item->format = format;
	item->lenght_format = ft_strlen(format);
	return (item);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_item		*item;

	item = setup(format);
	va_start(ap, format);
	va_end(ap);
	return (item->length_print);
}
