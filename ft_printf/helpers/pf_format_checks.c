/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:29:33 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 22:34:18 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool		pf_is_comp(char x)
{
	return (pf_is_flag(x) || pf_is_widpre(x) || pf_is_len(x));
}

t_bool		pf_is_flag(char x)
{
	return (x == '0' || x == '#' || x == '+' || x == '-' || x == ' ');
}

t_bool		pf_is_widpre(char x)
{
	return (ft_isdigit(x) || x == '*' || x == '.');
}

t_bool		pf_is_len(char x)
{
	return (x == 'h' || x == 'l' || x == 'j' || x == 'z' || x == 't' ||
																	x == 'L');
}

t_bool		pf_is_spec(char x)
{
	return (pf_is_float(x) || pf_is_int(x) || pf_is_strs(x));
}
