/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:40:31 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 22:27:23 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool		pf_is_base10(char x)
{
	return (pf_is_sint(x) || pf_is_uint(x));
}

t_bool		pf_is_basen10(char x)
{
	return (pf_is_uints(x));
}

int			pf_base(char x)
{
	return (pf_is_base10(x) ? 10 : pf_basen10(x));
}

int			pf_basen10(char x)
{
	return (x == 'o' ? 8 : 16);
}
