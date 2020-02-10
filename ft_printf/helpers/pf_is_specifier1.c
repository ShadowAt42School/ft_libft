/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_specifier1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:50:14 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 22:26:48 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	is_float(char x)
{
	return (x == 'f' || x == 'F' || x == 'e' || x == 'E' || x == 'g' || x == 'G'
													|| x == 'a' || x == 'A');
}

t_bool	is_int(char x)
{
	return (is_sint(x) || is_uint(x) || is_uints(x));
}

t_bool	is_sint(char x)
{
	return (x == 'd' || x == 'i' || x == 'D' || x == 'I');
}

t_bool	is_uint(char x)
{
	return (x == 'u' || x == 'U');
}

t_bool	is_uints(char x)
{
	return (x == 'o' || x == 'x' || x == 'X' || x == 'O' || is_pointer(x));
}
