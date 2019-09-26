/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:06:21 by maghayev          #+#    #+#             */
/*   Updated: 2019/09/25 22:15:38 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
**	Structs
*/
typedef struct	s_item
{
	const char*	format;
	char*		print;
	int			lenght_format;
	int			length_print;
}				t_item;

typedef struct	s_block
{
	short int	flags;
	int			width;
	int			precision;
	void*		value;
}				t_block;

/*
**	Wrappers: ft_printf, ft_sprintf
*/
t_item			*setup(const char *format);
int				ft_printf(const char *format, ...);

#endif
