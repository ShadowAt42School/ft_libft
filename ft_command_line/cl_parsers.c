/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_parsers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:41:24 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/22 21:38:21 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command_line.h"

static t_uint	g_order = 0;

void	cl_parse_argum(t_option *opt)
{
	if (opt->is_set == FALSE)
	{
		opt->is_set = TRUE;
		opt->order = g_order++;
	}
	ft_bzero(&opt->param, sizeof(opt->param));
}

void	cl_parse_argum_warg(t_option *opt, char *argm)
{
	if (opt->is_set == FALSE)
	{
		opt->is_set = TRUE;
		opt->order = g_order++;
	}
	opt->param.param = (void*)argm;
}
