/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_is_specifier1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:50:14 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 22:27:57 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	pf_is_float(char x)
{
	return (x == 'f' || x == 'F' || x == 'e' || x == 'E' || x == 'g' || x == 'G'
													|| x == 'a' || x == 'A');
}

t_bool	pf_is_int(char x)
{
	return (pf_is_sint(x) || pf_is_uint(x) || pf_is_uints(x));
}

t_bool	pf_is_sint(char x)
{
	return (x == 'd' || x == 'i' || x == 'D' || x == 'I');
}

t_bool	pf_is_uint(char x)
{
	return (x == 'u' || x == 'U');
}

t_bool	pf_is_uints(char x)
{
	return (x == 'o' || x == 'x' || x == 'X' || x == 'O' || pf_is_pointer(x));
}
