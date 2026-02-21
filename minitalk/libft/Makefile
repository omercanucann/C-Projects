# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oucan <oucan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 19:20:50 by oucan             #+#    #+#              #
#    Updated: 2025/01/13 20:15:33 by oucan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = libft.a 
SRCS = ft_printf.c ft_printf_utils.c ft_strchr.c ft_atoi.c
	  
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean: 
	rm -rf $(OBJS)

fclean: clean 
	rm -rf $(NAME)

re: fclean all
