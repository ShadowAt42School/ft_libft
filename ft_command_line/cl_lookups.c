/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_lookups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:22:24 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/17 19:52:27 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command_line.h"

t_int		cl_find_sopt(char opt, t_option *opts, size_t optsc)
{
	size_t	counter;

	counter = 0;
	while (counter < optsc)
	{
		if (opt == opts[counter].shortc)
			return (counter);
		counter++;
	}
	return (-1);
}

t_int		cl_find_lopt(char *opt, t_option *opts, size_t optsc)
{
	size_t	counter;

	counter = 0;
	while (counter < optsc)
	{
		if (ft_strcmp(opt, opts[counter].longc))
			return (counter);
		counter++;
	}
	return (-1);
}
