/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_is_specifier2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:50:14 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/12 21:34:13 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	pf_is_pointer(char x)
{
	return (x == 'p');
}

t_bool	pf_is_strs(char x)
{
	return (pf_is_str(x) || pf_is_char(x));
}

t_bool	pf_is_str(char x)
{
	return (x == 's' || x == 'S');
}

t_bool	pf_is_char(char x)
{
	return (x == 'c' || x == 'C');
}
