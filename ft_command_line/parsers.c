/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:41:24 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/03 21:29:51 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command_line.h"

void	cl_parse_argum(t_option *opt)
{
	if (opt->is_set == FALSE)
		opt->is_set = TRUE;
	ft_bzero(&opt->param, sizeof(opt->param));
}

void	cl_parse_argum_warg(t_option *opt, char *argm)
{
	if (opt->is_set == FALSE)
		opt->is_set = TRUE;
	opt->param.param = (void*)argm;
}
