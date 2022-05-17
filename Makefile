# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 16:22:28 by pgeeser           #+#    #+#              #
#    Updated: 2022/05/17 10:28:11 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = ft_printf.c ft_printf_helpers.c
BONUS_SRCS = ft_printf_bonus.c ft_printf_utils_bonus.c ft_printf_helpers_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

$(NAME): $(OBJS)
	make bonus -C ./libft
	cp ./libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

bonus: $(BONUS_OBJS)
	make bonus -C ./libft
	cp ./libft/libft.a $(NAME)
	ar -rcs $(NAME) $(BONUS_OBJS)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/

re: fclean all

norm:
	norminette $(SRCS) $(BONUS_SRCS) *.h

.PHONY:	all clean fclean re norm