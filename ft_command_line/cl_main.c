/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:36:19 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/27 22:06:28 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command_line.h"

char		*g_prog_name = NULL;

void	cl_init(char **args, t_option *options, size_t size)
{
	g_prog_name = *args;
	args++;
	cl_set_opts(options, size);
	cl_engine(args);
}
