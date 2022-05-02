# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 16:22:28 by pgeeser           #+#    #+#              #
#    Updated: 2022/05/02 16:05:16 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = ft_printf.c ft_printf_utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make bonus -C ./libft
	cp ./libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette *.c *.h

.PHONY:	all clean fclean re norm