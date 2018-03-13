# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 14:39:27 by jle-quer          #+#    #+#              #
#    Updated: 2016/09/29 13:02:04 by jle-quer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c ./ ./FT_PRINTF/

SRC_NAME =	ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_words.c \
			ft_isspace.c \
			ft_count.c \
			ft_islower.c \
			ft_isupper.c \
			ft_strchr_index.c \
			ft_count_wchar.c \
			ft_itoa_base.c \
			ft_power.c \
			ft_putint.c \
			ft_putwchar.c \
			ft_putwstr.c \
			ft_printf.c \
			check_display_block_d.c \
			check_display_block_o.c \
			check_display_block_p.c \
			check_display_block_u.c \
			check_display_block_x.c \
			check_format.c \
			check_format_2.c \
			display_block.c \
			set_c.c \
			set_d.c \
			set_format.c \
			set_hex.c \
			set_octal.c \
			set_tag.c \
			set_tag.c \
			set_p.c \
			set_s.c \
			set_u.c \
			set_wchar_s.c \
			tools.c \
			tools2.c \
			set_d_norm.c \
			get_next_line.c \
			ft_atoi_long.c \
			ft_lstpushback.c \
			ft_lstpushfront.c \
			ft_isint.c \
			ft_strndup.c \
			get_str_addr.c

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

OBJET = $(SRC_NAME:.c=.o)

all: $(NAME)
	@echo "Make In Progress"
	@echo "Make Done."

$(NAME): $(OBJET)
	@ar rc $(NAME) $(OBJET)
	@ranlib $(NAME)

%.o: %.c
	@gcc $(FLAGS) -I./INCLUDES -c $<

clean:
	@echo "Clean In Progress"
	@rm -f $(OBJET)
	@echo "Clean Done."

fclean: clean
	@rm -rf $(NAME)

re: fclean all

proper:
	@make
	@make clean

.PHONY: all, clean, fclean, re
