# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 21:42:08 by maghayev          #+#    #+#              #
#    Updated: 2020/02/12 21:34:06 by maghayev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
GREEN = "\033[32m\c"
RED = "\033[31m\c"
YELLOW = "\033[33m\c"
UNDERLINE = "\033[4m\c"
ORANGE = "\033[33m\c"
NC="\033[0m\c"

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC  = $(wildcard ft_printf/*.c ft_printf/helpers/*.c ft_command_line/*.c)
LIBS = -Iheaders/ -Ilibs/libft/headers/

DEPS = libft/

EPD = headers/ft_printf.h

%.o: %.c
	@echo $(ORANGE)
	$(CC) $(CFLAGS) $(LIBS) -g -o $@ -c $<
	@echo $(NC)

all: $(NAME)

$(NAME): | deps $(OBJECT)
	@ar rc $@ libs/libft/modules/*/*.o $(OBJECT)
	@ranlib $@
	@echo $(GREEN)
	@echo "Finished Building ft_stdio!"
	@echo $(NC)

objects: | deps $(OBJECT)
	@echo $(GREEN)
	@echo "Finished Building ft_stdio objects!"
	@echo $(NC)

deps: makedep
	@echo $(UNDERLINE)
	@echo "Finished building Dep. Libriaries"
	@echo $(NC)

makedep: libs/$(DEPS)
	@make objects -C $<
	@echo $(NC)

cleandep: libs/$(DEPS)
	@make clean -C $<

clean: cleandep
	@echo $(YELLOW)
	@echo "ft_stdio clean started"
	@/bin/rm -f $(OBJECT)
	@echo $(NC)
	@echo "..........."
	@echo $(YELLOW)
	@echo "ft_stdio clean finished"
	@echo $(NC)

fclean: clean
	@echo $(RED)
	@/bin/rm -f $(NAME)
	@echo "ft_stdio libriary has been cleaned."
	@echo $(NC)

re: fclean all

.PHONY: libftmake all clean fclean re
