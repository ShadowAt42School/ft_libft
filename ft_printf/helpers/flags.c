/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:29:33 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 22:35:23 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

t_bool	is_fsp(unsigned char x)
{
	return (x & 1 ? TRUE : FALSE);
}

t_bool	is_fsm(unsigned char x)
{
	return (x & 2 ? TRUE : FALSE);
}

t_bool	is_fspc(unsigned char x)
{
	return (x & 4 ? TRUE : FALSE);
}

t_bool	is_fhs(unsigned char x)
{
	return (x & 8 ? TRUE : FALSE);
}

t_bool	is_fzero(unsigned char x)
{
	return (x & 16 ? TRUE : FALSE);
}
