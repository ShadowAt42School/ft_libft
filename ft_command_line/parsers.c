/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:41:24 by maghayev          #+#    #+#             */
/*   Updated: 2020/01/16 22:41:43 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_command_line.h"

void cl_parse_option_sh(char *params, t_option *options, size_t opts_count)
{
	size_t	counter;
	size_t	checked_count;

	while (params)
	{
		counter = 0;
		checked_count = 0;
		while(counter < opts_count)
		{
			if (options[counter].shortc == *params)
			{
				if (options[counter].param.has_param)
				options[counter].is_set = TRUE;
			}
			counter++;
		}
	}
}
