/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:12:34 by maghayev          #+#    #+#             */
/*   Updated: 2020/01/28 22:33:11 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_command_line.h"

/*
** t_option	options[5];
** options[0] = (t_option){.shortc = 'c', .longc = "adasd"};
*/
void	cl_engine(char **args, t_option *options, size_t opts_count)
{
	while (**args)
	{
		if (**args == '-' && (**args + 1) == '-')
			cl_parse_option_l();
		else if (**args == '-')
			cl_parse_option_s();
		else
			cl_parse_param();
		args++;
	}
}

void	cl_engine_options_s(char *opts)
{
	char	opt;

	while (*opts && (opt = *opts))
	{
		cl_parse_option_sh(opt);
	}
}
