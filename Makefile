# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 16:22:28 by pgeeser           #+#    #+#              #
#    Updated: 2022/04/25 16:44:23 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = printf.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C ./libft
	ar -rcT $(NAME) $(OBJS) ./libft/libft.a

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette *.c *.h

.PHONY:	all clean fclean re norm