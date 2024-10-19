# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zserobia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 15:35:11 by zserobia          #+#    #+#              #
#    Updated: 2024/09/09 15:35:14 by zserobia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAMESC =	main.c utils.c error.c utils1.c utils2.c

NAMESO = $(NAMESC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = cc

all: $(NAME)

$(NAME): $(NAMESO)
	cc -o $(NAME) $(NAMESO)

%.o: %.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAMESO)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean
