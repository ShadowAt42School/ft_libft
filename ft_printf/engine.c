/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:02:29 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/06 23:39:05 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"
#include <stdio.h>

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
			ft_lstaddend(&pieces, parse_format(ap, &result->format));
			continue;
		}
		clean_str_len = ft_strdelim(&clean_str, result->format, '%');
		ft_lstaddend(&pieces, ft_lstnew(clean_str, clean_str_len));
		result->format += clean_str_len;
	}
	finalize(result, pieces);
}

t_list	*parse_format(va_list *ap, const char **format_origin)
{
	t_formater	formatter;

	ft_bzero(&formatter, sizeof(t_formater));
	parse_flags(format_origin, &formatter);
	parse_width_precision(format_origin, &formatter, ap);
	parse_width_precision(format_origin, &formatter, ap);
	parse_length(format_origin, &formatter);
	parse_specifier(format_origin, &formatter, ap);
	build_decorators(&formatter);
	return (build_format(&formatter));
}

t_list	*build_format(t_formater *formater)
{
	char			*result;
	unsigned int	total_length;
	unsigned int	str_start;

	total_length = formater->width;
	length_length(&total_length, formater);
	flags_length(&total_length, formater);
	result = ft_strnew(total_length);
	if (formater->width > 0)
		ft_memset(result,
			formater->decorators.is_pad_zeros &&
								!formater->decorators.is_precision ? '0' : ' ',
			total_length);
	str_start = total_length - formater->value_length;
	if (formater->decorators.is_precision)
		build_precision(&result, formater, str_start);
	build_specifier(&result, formater, str_start);
	build_flags(&result, formater, str_start);
	return (ft_lstnew(result, total_length));
}

void	finalize(t_result *result, t_list *pieces)
{
	t_list			*pstart;
	t_list			*poped;
	unsigned int	cur_len;

	cur_len = 0;
	pstart = pieces;
	while (pstart)
	{
		result->length_print += pstart->content_size;
		pstart = pstart->next;
	}
	result->print = ft_strnew(result->length_print);
	pstart = pieces;
	while (pstart && (poped = pstart))
	{
		ft_memcpy(result->print + cur_len, poped->content, poped->content_size);
		cur_len += poped->content_size;
		free(poped->content);
		free(poped);
		pstart = pstart->next;
	}
}
