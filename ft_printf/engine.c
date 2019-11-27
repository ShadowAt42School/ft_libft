/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:02:29 by maghayev          #+#    #+#             */
/*   Updated: 2019/11/26 21:36:00 by maghayev         ###   ########.fr       */
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
			if (!*result->format)
				break ;
			ft_lstaddend(&pieces, parse_format(ap, &result->format));
			continue;
		}
		clean_str_len = ft_strdelim(&clean_str, result->format, '%');
		ft_lstaddend(&pieces, ft_lstnewp(clean_str, clean_str_len));
		result->format += clean_str_len;
	}
	finalize(result, pieces);
}

t_list	*parse_format(va_list *ap, const char **format_origin)
{
	t_formater	formatter;

	ft_bzero(&formatter, sizeof(t_formater));
	while (!ISSPECIF(**format_origin) && ISANYOFCOMP(**format_origin))
	{
		if (ISFLAG(**format_origin))
			parse_flags(format_origin, &formatter, ap);
		if (ISWIDPRE(**format_origin))
			parse_width_precision(format_origin, &formatter, ap);
		if (ISLENGTH(**format_origin))
			parse_length(format_origin, &formatter, ap);
	}
	parse_specifier(format_origin, &formatter, ap);
	build_decorators(&formatter);
	return (build_format(&formatter));
}

t_list	*build_format(t_formater *fmt)
{
	char			*result;
	unsigned int	total_length;

	total_length = 0;
	if (fmt->specifier)
	{
		prepare_length(&total_length, fmt);
		result = ft_strnew(total_length);
		if (fmt->width > 0)
			ft_memset(result, fmt->decorators.is_pad_zeros &&
					!fmt->decorators.is_precision ? '0' : ' ', total_length);
		if (fmt->decorators.is_precision)
			build_precision(&result, fmt, fmt->decorators.is_ljustify
						? fmt->len.aux : total_length - fmt->len.processed);
		build_specifier(&result, fmt, fmt->decorators.is_ljustify ?
					(fmt->len.processed - fmt->len.value + fmt->len.aux) :
												total_length - fmt->len.value);
		build_flags(&result, fmt, fmt->decorators.is_ljustify ? 0
						: total_length - fmt->len.processed - fmt->len.aux);
	}
	return (ft_lstnewp(result, total_length));
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
		if (poped->content_size != 0)
		{
			ft_memcpy(result->print + cur_len,
										poped->content, poped->content_size);
			cur_len += poped->content_size;
			free(poped->content);
			free(poped);
		}
		pstart = pstart->next;
	}
}
