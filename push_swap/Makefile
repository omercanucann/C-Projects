# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oucan <oucan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 15:52:07 by oucan             #+#    #+#              #
#    Updated: 2025/03/09 18:45:53 by oucan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LIBFTDIR = libft/
OBJ_DIR = obj/
SRC_DIR = srcs/

SRC_1 = srcs/push_swap.c \

SRC_2 =	srcs/process.c \
		srcs/case_ab.c \
		srcs/case_ba.c \
		srcs/ft_rotate_and_push.c \
		srcs/ft_utils_4.c \
		srcs/ft_utils_2.c \
		srcs/ft_utils_3.c \
		srcs/lst_utils.c \
		srcs/lst_utils_2.c \
		srcs/ft_seperate_args.c \
		srcs/ft_list_args.c \
		srcs/ft_add_back.c \
		srcs/ft_sort.c \
		
			

OBJ_1 = ${SRC_1:.c=.o}
OBJ_2 = ${SRC_2:.c=.o}


INCLUDE = -L ./libft -lft

.c.o:
	${CC} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ_1} ${OBJ_2}
	make -C $(LIBFTDIR)
	${CC} ${FLAGS} ${OBJ_1} ${OBJ_2} -o ${NAME} ${INCLUDE}


all: ${NAME}


clean:
	${RM} ${OBJ_1} ${OBJ_2} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: clean all

.PHONY: all clean fclean re