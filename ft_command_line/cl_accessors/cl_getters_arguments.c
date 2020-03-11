/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_getters_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:43:09 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/10 21:56:05 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cl_accessors.h"

size_t		g_argums_count;
char		**g_arguments;

size_t		cl_get_argums_count(void)
{
	return (g_argums_count);
}

char		**cl_get_raw_arguments(void)
{
	return (g_arguments);
}

char		*cl_get_argument(void)
{
	char	*argument;

	if (!g_arguments)
		return (NULL);
	argument = *g_arguments;
	if (!argument)
		return (NULL);
	g_arguments++;
	return (argument);
}
