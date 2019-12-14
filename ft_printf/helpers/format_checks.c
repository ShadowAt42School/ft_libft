/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:29:33 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 22:54:19 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

t_bool		is_comp(char x)
{
	return (is_flag(x) || is_widpre(x) || is_len(x));
}

t_bool		is_flag(char x)
{
	return (x == '0' || x == '#' || x == '+' || x == '-' || x == ' ');
}

t_bool		is_widpre(char x)
{
	return (ft_isdigit(x) || x == '*' || x == '.');
}

t_bool		is_len(char x)
{
	return (x == 'h' || x == 'l' || x == 'j' || x == 'z' || x == 't' ||
																	x == 'L');
}

t_bool		is_spec(char x)
{
	return (is_float(x) || is_int(x) || is_strs(x));
}
