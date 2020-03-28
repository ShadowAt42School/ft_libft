/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:12:34 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/27 22:05:52 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command_line.h"

extern char		*g_prog_name;

/*
** t_option	options[5];
** options[0] = (t_option){.shortc = 'c', .longc = "adasd"};
*/

void	cl_engine(char **args)
{
	size_t	opts_count;

	opts_count = cl_get_opts_count();
	if (opts_count == 0)
		return ;
	while (*args)
	{
		if (**args == '-' && *(*args + 1) == '-' && *(*args + 2) == '\0')
		{
			cl_engine_argument(++args);
			break ;
		}
		else if (**args == '-' && *(*args + 1) == '-' && *(*args + 2) != '\0')
			cl_engine_options_l(args, cl_get_raw_options(), opts_count);
		else if (**args == '-')
			cl_engine_options_s(args, cl_get_raw_options(), opts_count);
		else
		{
			cl_engine_argument(args);
			break ;
		}
		args++;
	}
}

void	cl_engine_options_s(char **argums, t_option *opts, size_t optsc)
{
	char	*argum;
	t_int	opti;

	argum = *argums + 1;
	while (*argum)
	{
		opti = cl_find_sopt(*argum, opts, optsc);
		if (opti == -1)
		{
			ft_fdprintf(STDERR_FILENO, "%s: Option %c is not defined\n",
														g_prog_name, *argum);
			exit(EXIT_FAILURE);
		}
		if (opts[opti].param.has_param)
			cl_parse_argum_warg(&opts[opti], *(argums + 1));
		else
			cl_parse_argum(&opts[opti]);
		argum++;
	}
}

void	cl_engine_options_l(char **argums, t_option *opts, size_t optsc)
{
	char	*argum;
	t_int	opti;

	argum = *argums + 2;
	while (*argum)
	{
		opti = cl_find_lopt(argum, opts, optsc);
		if (opti == -1)
		{
			ft_fdprintf(STDERR_FILENO, "%s: Option %s is not defined\n",
															g_prog_name, argum);
			exit(EXIT_FAILURE);
		}
		if (opts[opti].param.has_param)
			cl_parse_argum_warg(&opts[opti], *(argums + 1));
		else
			cl_parse_argum(&opts[opti]);
		argum++;
	}
}

void	cl_engine_argument(char **argums)
{
	if (!argums || !*argums)
		return ;
	cl_set_arguments(argums);
}

void	cl_sort_arguments(t_bool (*comp)(char *, char *))
{
	ft_string_bubble_sort(cl_get_raw_arguments(), cl_get_argums_count(), comp);
}
