/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:40:53 by maghayev          #+#    #+#             */
/*   Updated: 2019/11/25 20:33:23 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

static void	setup(const char *format, t_result *result)
{
	ft_bzero(result, sizeof(t_result));
	result->format = format;
	result->lenght_format = ft_strlen(format);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_result	result;

	ft_bzero(&result, sizeof(result));
	setup(format, &result);
	va_start(ap, format);
	ft_engine(&ap, &result);
	va_end(ap);
	write(1, result.print, result.length_print);
	ft_strdel(&result.print);
	return (result.length_print);
}
