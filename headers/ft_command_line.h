/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:10:40 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/10 23:29:55 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMAND_LINE_H
# define FT_COMMAND_LINE_H
# include "libft.h"

# define ERROR_PARSING_ERROR 500
# define ERROR_NO_OPTION 404

typedef struct	s_option_param {
	t_bool			has_param;
	t_bool			mult;
	void			*param;
	char			type;
}				t_option_param;

typedef struct	s_option {
	char			shortc;
	char			*longc;
	char			*desc;
	t_bool			mandatory;
	t_bool			is_set;
	t_option_param	param;
	t_uint			order;
}				t_option;

void			cl_init(char **args, t_option *options, size_t size);
void			cl_engine(char **args);
void			cl_engine_options_s(char **argums,
												t_option *opts, size_t optsc);
void			cl_engine_options_l(char **argums,
												t_option *opts, size_t optsc);
void			cl_engine_argument(char **argums);

/*
**	Parsers
*/
void			cl_parse_argum(t_option *opt);
void			cl_parse_argum_warg(t_option *opt, char *argm);

/*
**	Accessors
*/
void			cl_set_opts(t_option *opts, size_t opts_count);
void			cl_set_opts_count(size_t opts_count);
void			cl_set_arguments(char **args);
void			cl_set_argums_count(size_t argums_count);

size_t			cl_get_opts_count(void);
t_option		*cl_get_raw_options(void);
t_option		*cl_get_sopt(char opt);
t_option		*cl_get_lopt(char *opt);

size_t			cl_get_argums_count(void);
char			***cl_get_raw_arguments(void);
char			*cl_get_argument();
void			cl_sort_arguments(t_bool (comp)(char *, char *));
/*
**	Helper Functions
*/
t_int			cl_find_sopt(char opt, t_option *opts, size_t optsc);
t_int			cl_find_lopt(char *opt, t_option *opts, size_t optsc);
#endif
