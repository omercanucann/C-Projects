# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oucan <oucan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/27 15:37:18 by oucan             #+#    #+#              #
#    Updated: 2025/07/27 15:55:46 by oucan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Project files
SRCS = main.c \
       philosophers.c \
       utils.c \
       reaper.c \
       table.c \
       time.c \
       utils_2.c \
	stop.c \
       utils_3.c \
       value.c 
OBJS = $(SRCS:.c=.o)
INC = philo.h
NAME = philosophers

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re