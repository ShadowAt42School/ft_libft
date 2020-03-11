/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_getters_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:43:09 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/10 21:55:01 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cl_accessors.h"

size_t		g_opts_count;
t_option	*g_options;

size_t		cl_get_opts_count(void)
{
	return (g_opts_count);
}

t_option	*cl_get_raw_options(void)
{
	return (g_options);
}

t_option	*cl_get_sopt(char opt)
{
	int		option;

	if (!g_options)
		return (NULL);
	option = cl_find_sopt(opt, g_options, g_opts_count);
	if (option == -1 || (g_options + option)->is_set == FALSE)
		return (NULL);
	return (g_options + option);
}

t_option	*cl_get_lopt(char *opt)
{
	int		option;

	if (!g_options)
		return (NULL);
	option = cl_find_lopt(opt, g_options, g_opts_count);
	if (option == -1 || (g_options + option)->is_set == FALSE)
		return (NULL);
	return (g_options + option);
}
