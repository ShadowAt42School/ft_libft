/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_line.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:10:40 by maghayev          #+#    #+#             */
/*   Updated: 2020/01/16 22:21:32 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMAND_LINE_H
# define FT_COMMAND_LINE_H
# include "../libs/libft/libft.h"

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
}				t_option;

void			cl_engine(t_option *options, char **args);

#endif
