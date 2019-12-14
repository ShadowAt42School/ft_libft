/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:40:31 by maghayev          #+#    #+#             */
/*   Updated: 2019/12/13 22:45:05 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

t_bool		is_base10(char x)
{
	return (is_sint(x) || is_uint(x));
}

t_bool		is_basen10(char x)
{
	return (is_uints(x));
}

int			base(char x)
{
	return (is_base10(x) ? 10 : basen10(x));
}

int			basen10(char x)
{
	return (x == 'o' ? 8 : 16);
}
