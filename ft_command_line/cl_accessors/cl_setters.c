/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_setters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:43:09 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/10 22:10:03 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cl_accessors.h"

size_t		g_opts_count = 0;
size_t		g_argums_count = 0;
char		**g_arguments = NULL;
t_option	*g_options = NULL;

void		cl_set_opts(t_option *opts, size_t opts_count)
{
	g_options = opts;
	cl_set_opts_count(opts_count);
}

void		cl_set_opts_count(size_t opts_count)
{
	g_opts_count = opts_count;
}

void		cl_set_argums_count(size_t argums_count)
{
	g_argums_count = argums_count;
}

void		cl_set_arguments(char **args)
{
	char	**argsc;
	size_t	count;

	argsc = args;
	g_arguments = args;
	count = 0;
	while (*argsc)
	{
		count++;
		argsc++;
	}
	cl_set_argums_count(count);
}
