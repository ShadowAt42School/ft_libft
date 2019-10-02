/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:06:21 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/01 23:53:51 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "lib/libft/headers/libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <inttypes.h>

/*
**	Defines for Flags and Length and Specifier representation	**
*/
# define ISFLAG1(x)	(x == '+' || x == '-' || x == ' ' ? TRUE : FALSE)
# define ISFLAG(x)	(x == '0' || ISFLAG1(x) || x == '#' ? TRUE : FALSE)

/*
**	Flag checks against flag mask	**
*/
# define ISFLAGSP(x) 	(x & 1 ? TRUE : FALSE)
# define ISFLAGSM(x) 	(x & 2 ? TRUE : FALSE)
# define ISFLAGSPC(x) 	(x & 4 ? TRUE : FALSE)
# define ISFLAGHS(x) 	(x & 8 ? TRUE : FALSE)
# define ISFLAGZERO(x) 	(x & 16 ? TRUE : FALSE)

# define SIGNPOSSIBLE(x) (x == 'd'|| x == 'i' || x == 'c' ? TRUE : FALSE)

/*
**	Length
*/
# define NO	0
# define H	1
# define HH 2
# define L 	3
# define LL 4
# define J 	5
# define Z 	6
# define T 	7
# define LF	8

# define ISLENGTH(x)	(x == 'h' || x == 'l' || x == 'j' || ISLENGTH1(x))
# define ISLENGTH1(x)	(x == 'z' || x == 't' || x == 'L')

# define ISFLOAT(x)		(x == 'f' || x == 'F' || x == 'e' || ISFLOAT1(x))
# define ISFLOAT1(x)	(x == 'E' || x == 'g' || x == 'G' || ISFLOAT2(x))
# define ISFLOAT2(x)	(x == 'a' || x == 'A')

/*
**	Varg
**	Union for all possible lengths(specifier agnostic)	**
*/
union				u_argument {
	char					schar;
	unsigned char			uchar;
	char					*str;
	short int				shint;
	int						intd;
	long int				lint;
	long long int			llint;
	unsigned int			uintd;
	unsigned short int		ushintd;
	unsigned long int		ulint;
	unsigned long long int	ullint;
	double					dnumber;
	long double				ldnumber;
	wchar_t					wchar;
	wchar_t					*wstr;
	size_t					sizet;
	intmax_t				intmax;
	uintmax_t				uintmax;
	void					*pspec;
};

/*
**	Structs
*/
typedef struct		s_string_decoration
{
	t_bool					is_left_justify;
	t_bool					is_force_sign;
	t_bool					is_blank_space;
	t_bool					is_preceed_ox;
	t_bool					is_capital;
	t_bool					is_force_decimal;
	t_bool					is_pad_zeros;
}					t_string_decoration;

typedef struct		s_formater
{
	unsigned char			flags;
	unsigned int			width;
	unsigned int			precision;
	unsigned short int		length;
	unsigned char			specifier;
	t_string_decoration		decorators;
	union u_argument		value;
}					t_formater;

typedef	struct		s_result
{
	const char				*format;
	char					*print;
	int						lenght_format;
	int						length_print;
}					t_result;

/*
**	Wrappers: ft_printf, ft_sprintf
*/
t_result			*setup(const char *format);
int					ft_printf(const char *format, ...);

/*
**	Engine
*/
void				ft_engine(va_list *ap, t_result *result);
t_list				*parse_format(va_list *ap, const char **format_origin);
t_list				*build_format(t_formater *formater);

/*
**	Format Parsers
*/
void				parse_flags(const char **format, t_formater *formater);
void				parse_width_precision(
						const char **format, t_formater *formater, va_list *ap);
void				parse_length(const char **format, t_formater *formater);

void				parse_specifier(
						const char **format, t_formater *formater, va_list *ap);
void				build_decorators(t_formater *formater);

#endif
