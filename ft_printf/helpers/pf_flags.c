/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:29:33 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 22:27:30 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	pf_is_fsp(unsigned char x)
{
	return (x & 1 ? TRUE : FALSE);
}

t_bool	pf_is_fsm(unsigned char x)
{
	return (x & 2 ? TRUE : FALSE);
}

t_bool	pf_is_fspc(unsigned char x)
{
	return (x & 4 ? TRUE : FALSE);
}

t_bool	pf_is_fhs(unsigned char x)
{
	return (x & 8 ? TRUE : FALSE);
}

t_bool	pf_is_fzero(unsigned char x)
{
	return (x & 16 ? TRUE : FALSE);
}
