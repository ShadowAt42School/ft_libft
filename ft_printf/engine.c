/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:02:29 by maghayev          #+#    #+#             */
/*   Updated: 2019/09/29 22:01:40 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"

void	ft_engine(va_list *ap, t_result *result)
{
	t_list	*pieces;
	char	*clean_str;
	int		clean_str_len;

	pieces = NULL;
	while (*result->format)
	{
		if (*result->format == '%')
		{
			result->format++;
			ft_lstadd(&pieces, parse_format(ap, &result->format));
			continue;
		}
		clean_str = ft_strdupdelim(result->format, '%');
		clean_str_len = ft_strlen(clean_str);
		ft_lstadd(&pieces, ft_lstnew(clean_str, clean_str_len));
		result->format += clean_str_len;
	}
}

t_list	*parse_format(va_list *ap, const char **format_origin)
{
	t_list		*piece;
	t_formater	formatter;

	ft_bzero(&formatter, sizeof(t_formater));
	parse_flags(format_origin, &formatter);
	parse_width_precision(format_origin, &formatter, ap);
	parse_width_precision(format_origin, &formatter, ap);
	piece = ft_lstnew(NULL, 0);
	return (piece);
}
