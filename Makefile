# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 16:22:28 by pgeeser           #+#    #+#              #
#    Updated: 2022/05/12 11:37:25 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = ft_printf.c ft_printf_utils.c ft_printf_helpers.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make bonus -C ./libft
	cp ./libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

bonus: all

clean:
	rm -rf $(OBJS)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/

re: fclean all

norm:
	norminette $(SRCS) *.h

.PHONY:	all clean fclean re norm