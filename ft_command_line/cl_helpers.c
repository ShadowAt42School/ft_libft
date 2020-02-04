/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:43:09 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/03 22:52:23 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_command_line.h"

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

char		*cl_get_argument()
{
	char	*argument;

	if (!g_arguments)
		return NULL;
	argument = *g_arguments;
	if (!argument)
		return (NULL);
	g_arguments++;
	return (argument);
}

t_option	*cl_get_copt(char opt)
{
	int		option;

	if (!g_options)
		return NULL;
	option = cl_find_sopt(opt, g_options, g_opts_count);
	if (option == -1)
		return (NULL);
	return (g_options + option);
}
