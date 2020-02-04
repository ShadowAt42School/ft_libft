# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 21:42:08 by maghayev          #+#    #+#              #
#    Updated: 2020/02/03 22:05:28 by maghayev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
ORANGE = "\033[33m\c"
PURPLE = "\033[35m\c"
NC="\033[0m\c"
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPS = headers/lib/ft_printf.h headers/lib/ft_stdio.h
SRC  = $(wildcard ft_printf/*.c ft_printf/helpers/*.c ft_command_line/*.c)

ROOTLIBS = libs/libft/libft.a

OBJECT = $(SRC:.c=.o)

%.a: libftmake
	@echo "Finished building Dep. Libriaries"
	@echo $(NC)

%.o: %.c $(DEPS)
	@echo $(ORANGE)
	$(CC) $(CFLAGS) -o $@ $<
	@echo $(NC)

all: $(NAME)

$(NAME): $(ROOTLIBS) $(OBJECT)
	@ar rc $@ libs/libft/modules/*/*.o $(OBJECT)
	@ranlib $@
	@echo "Finished Building ft_stdio!"

libftmake:
	@make -C libs/libft/
	@echo $(NC)

clean:
	@make clean -C libs/libft/
	@echo $(PURPLE)
	@echo "whaaaaa, cleaning printf..."
	@/bin/rm -f $(OBJECT)
	@echo "There! Done!"
	@echo $(NC)

fclean: clean
	@make fclean -C libs/libft/
	@/bin/rm -f $(NAME)
	@echo "ft_stdio.a has been deleted! *sign*"

re: fclean all

.PHONY: libftmake all clean fclean re
