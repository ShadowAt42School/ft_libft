/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:48:01 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 22:55:26 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

int		flhslen(char x)
{
	return (x == 'o' ? 1 : 2);
}

char	*flhsstr(char x)
{
	return (x == 'o' ? "0" : flhsstrx(x));
}

char	*flhsstrx(char x)
{
	return (x == 'x' || x == 'p' ? "0x" : "0X");
}

t_bool	caplen(char x)
{
	return (x == 'D' || x == 'O' || x == 'U' || x == 'S' || x == 'C');
}
