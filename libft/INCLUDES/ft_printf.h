/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 12:24:47 by jle-quer          #+#    #+#             */
/*   Updated: 2016/03/14 14:25:57 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <wchar.h>

typedef struct	s_struct
{
	char		*block;
	int			hash;
	int			moins;
	int			plus;
	int			zero;
	int			space;
	int			larg;
	int			prec;
	int			hh;
	int			h;
	int			l;
	int			ll;
	int			j;
	int			z;
	char		type;
}				t_struct;

int				g_ret;

int				ft_printf(const char *format, ...);
int				check_format(const char *format);
int				check_options(const char format, t_struct *form);
int				check_type(const char format);
int				check_minimal_large(const char format, t_struct *form);
int				check_precision(const char format, t_struct *form);
int				check_block(char *block, t_struct *form);
int				set_block(const char *format, va_list va);
int				display_block(t_struct *form, va_list va, int i);
int				ft_count_base(unsigned long n, int base);

long long		check_display_block_d(t_struct *form, va_list va);
uintmax_t		check_display_block_o(t_struct *form, va_list va);
uintmax_t		check_display_block_x(t_struct *form, va_list va);
uintmax_t		check_display_block_u(t_struct *form, va_list va);
unsigned long	check_display_block_p(va_list va);

void			set_format(const char *format, va_list va);
void			check_size_modifier(const char *format, t_struct *form);
void			init_struct(t_struct *form);
void			checkflags(t_struct *form, char a, char b);
void			set_c(t_struct *form, va_list va);
void			set_s(t_struct *form, va_list va);
void			set_wchar_s(t_struct *form, va_list va);

char			*set_moins_d_2(t_struct *form, char *str, long long n,
				char *larg);
char			*set_moins_d_norm(t_struct *form, char *s, char *larg,
				long long n);
char			*set_d_0_neg(char *str, int nbr0, long long n);
char			*set_d_plus_space(char *str, char c);
char			*set_larg(t_struct *form, char *str);
char			*place(int n, char c);
char			*place_s(int n, char c);
char			*set_upper(char *str);
char			*set_d(t_struct *form, va_list va);
char			*set_hex(t_struct *form, va_list va);
char			*set_u(t_struct *form, va_list va);
char			*set_p(t_struct *form, va_list va);
char			*set_tag(t_struct *form);
char			*set_octal(t_struct *form, va_list va);

#endif
