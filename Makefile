# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 21:42:08 by maghayev          #+#    #+#              #
#    Updated: 2019/09/29 20:07:53 by maghayev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
ORANGE = "\033[33m\c"
RED = "\033[31m\c"
NC="\033[0m\c"
CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g
DEPS = headers/lib/ft_printf.h headers/lib/ft_stdio.h
SRC  = $(wildcard ft_printf/*.c)

ROOTLIBS = headers/lib/libft/libft.a

OBJECT = $(SRC:.c=.o)

%.a: libftmake
	@echo $(RED)
	@echo "Finished building Dep. Libriaries"
	@echo $(NC)

%.o: %.c $(DEPS)
	@echo $(ORANGE)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo $(NC)

all: $(NAME)

$(NAME): $(ROOTLIBS) $(OBJECT)
	@ar rc $@ headers/lib/libft/modules/*/*.o $(OBJECT)
	@ranlib $@
	@echo "Finished Building Printf!"

libftmake:
	@make -C headers/lib/libft/

clean:
	make clean -C headers/lib/libft/
	@echo $(RED)
	@echo "*sadly* Cleanning LibFT... Wait... *sniffs*"
	@/bin/rm -f $(OBJECT)
	@echo "Cleaned LibFT! Bye Bye! *without intusiasm*"
	@echo $(NC)

fclean: clean
	make fclean -C headers/lib/libft/
	@/bin/rm -f $(NAME)
	@echo "LibFT .a has been deleted! *sign*"

re: fclean all

.PHONY: libftmake all clean fclean re
