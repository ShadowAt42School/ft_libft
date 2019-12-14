/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_specifier2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:50:14 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 23:57:30 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

t_bool	is_pointer(char x)
{
	return (x == 'p');
}

t_bool	is_strs(char x)
{
	return (is_str(x) || is_char(x));
}

t_bool	is_str(char x)
{
	return (x == 's' || x == 'S');
}

t_bool	is_char(char x)
{
	return (x == 'c' || x == 'C');
}
