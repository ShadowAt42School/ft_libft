/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:41:24 by maghayev          #+#    #+#             */
/*   Updated: 2020/01/29 22:17:03 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_command_line.h"

void	cl_parse_argum(t_option *opt)
{
	opt->is_set = TRUE;
	ft_bzero(&opt->param, sizeof(opt->param));
}

void	cl_parse_argum_warg(t_option *opt, char *argm)
{
	opt->is_set = TRUE;
	opt->param.param = (void*)argm;
}
