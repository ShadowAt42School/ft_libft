/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:06:21 by maghayev          #+#    #+#             */
/*   Updated: 2019/11/10 17:49:14 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "lib/libft/headers/libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <inttypes.h>

# define ISANYOFCOMP(x) (ISFLAG(x) || ISWIDPRE(x) || ISLENGTH(x) ? TRUE : FALSE)

/*
**	Defines for Flags and Length and Specifier representation	**
*/
# define ISFLAG(x)		(x == '0' || ISFLAG1(x) || x == '#' ? TRUE : FALSE)
# define ISFLAG1(x)		(x == '+' || x == '-' || x == ' ' ? TRUE : FALSE)
# define ISWIDPRE(x)	(IS_DIGIT(x) || x == '*' || x == '.' ? TRUE : FALSE)
# define ISLENGTH(x)	(x == 'h' || x == 'l' || x == 'j' || ISLENGTH1(x))
# define ISLENGTH1(x)	(x == 'z' || x == 't' || x == 'L' ? TRUE : FALSE)
# define ISSPECIF(x)	(FLOAT(x) || INTSPEC(x) || STRS(x))

/*
**	Flag checks against flag mask	**
*/
# define ISFLAGSP(x) 	(x & 1 ? TRUE : FALSE)
# define ISFLAGSM(x) 	(x & 2 ? TRUE : FALSE)
# define ISFLAGSPC(x) 	(x & 4 ? TRUE : FALSE)
# define ISFLAGHS(x) 	(x & 8 ? TRUE : FALSE)
# define ISFLAGZERO(x) 	(x & 16 ? TRUE : FALSE)

# define FLHSLEN(x)	(x == 'o' ? 1 : 2)
# define FLHSSTR(x)	(x == 'o' ? "0" : FLHSSTR1(x))
# define FLHSSTR1(x)(x == 'x' || x == 'p' ? "0x" : "0X")

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
# define DSTR_MAX 50
# define CAPLEN(x) (x == 'D' || x == 'O' || x == 'U' || x == 'S' || x == 'C')

/*
**	Specifiers check definitions
*/
# define FLOAT(x)		(x == 'f' || x == 'F' || x == 'e' || FLOAT1(x))
# define FLOAT1(x)		(x == 'E' || x == 'g' || x == 'G' || FLOAT2(x))
# define FLOAT2(x)		(x == 'a' || x == 'A' ? TRUE : FALSE)

# define INTSPEC(x) 	(INTSIGN(x) || INTUSIGN(x) || INTUSIGNS(x))
# define INTSIGN(x) 	(x == 'd' || x == 'i' || INTSIGN1(x) ? TRUE : FALSE)
# define INTSIGN1(x) 	(x == 'D' || x == 'I' ? TRUE : FALSE)
# define INTUSIGN(x) 	(x == 'u' || x == 'U' ? TRUE : FALSE)
# define INTUSIGNS(x) 	(x == 'o' || x == 'x' || x == 'X' || INTUSIGNS1(x))
# define INTUSIGNS1(x) 	(x == 'O' || POINTER(x))
# define POINTER(x) 	(x == 'p' ? TRUE : FALSE)

# define STRS(x)		(STRING(x) || CHART(x))
# define STRING(x)		(x == 'S' || x == 's' ? TRUE : FALSE)
# define CHART(x)		(x == 'c' || x == 'C' ? TRUE : FALSE)

/*
**	Base determination
*/
# define ISBASE10(x)	(INTSIGN(x) || INTUSIGN(x) || x == 'c' ? TRUE : FALSE)
# define ISBASEN10(x)	(INTUSIGNS(x))
# define BASE(x) 		(ISBASE10(x) ? 10 : BASEN10(x))
# define BASEN10(x)		(x == 'o' ? 8 : 16)

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
	ptrdiff_t				ptrdiff;
};

/*
**	Structs
*/
typedef struct		s_string_decoration
{
	t_bool					is_ljustify;
	t_bool					is_force_sign;
	t_bool					is_blank_space;
	t_bool					is_preceed_ox;
	t_bool					is_force_decimal;
	t_bool					is_capital;
	t_bool					is_pad_zeros;
	t_bool					is_precision;

}					t_string_decoration;

typedef struct		s_integer_values
{
	long long int			llin;
	unsigned long long int	ullin;
	char					buffer[DSTR_MAX];
}					t_integer_values;

typedef struct		s_fmtlen
{
	int						aux;
	int						value;
	int						processed;
}					t_fmtlen;

typedef struct		s_formater
{
	unsigned char			flags;
	int						width;
	int						precision;
	unsigned short int		length;
	unsigned char			specifier;
	t_fmtlen				len;
	t_string_decoration		decorators;
	t_integer_values		intval;
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
void				finalize(t_result *result, t_list *pieces);

/*
**	Format Parsers
*/
void				parse_flags(
						const char **format, t_formater *formater, void *ap);
void				parse_width_precision(
						const char **format, t_formater *formater, va_list *ap);
void				parse_length(
						const char **format, t_formater *formater, void *ap);
void				parse_specifier(
						const char **format, t_formater *formater, va_list *ap);
void				build_decorators(t_formater *formater);

/*
**	Format Result Length
*/
void				prepare_length(
								unsigned int *current_length, t_formater *form);

/*
**	Format String Builders
*/
void				build_flags(
						char **res, t_formater *fmt, unsigned int str_start);
void				build_precision(
						char **res, t_formater *fmt, unsigned int str_start);
void				build_specifier(
						char **res, t_formater *fmt, unsigned int str_start);

#endif
