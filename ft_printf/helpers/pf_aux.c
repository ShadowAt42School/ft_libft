/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:48:01 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/12 21:34:11 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_flhslen(char x)
{
	return (x == 'o' ? 1 : 2);
}

char	*pf_flhsstr(char x)
{
	return (x == 'o' ? "0" : pf_flhsstrx(x));
}

char	*pf_flhsstrx(char x)
{
	return (x == 'x' || x == 'p' ? "0x" : "0X");
}

t_bool	pf_caplen(char x)
{
	return (x == 'D' || x == 'O' || x == 'U' || x == 'S' || x == 'C');
}
