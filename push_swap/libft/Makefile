# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oucan <oucan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:34:24 by yogun             #+#    #+#              #
#    Updated: 2025/03/09 19:14:08 by oucan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_memcpy.c ft_split.c ft_strchr.c ft_strdup.c ft_strlen.c ft_substr.c ft_strlcpy.c ft_strjoin.c
			
OBJS	= $(SRCS:.c=.o)
HDRS    = libft.h
NAME    = libft.a
RM 		= rm -rf
CC 		= cc
AR  	= ar -crs
FLAGS   = -Wall -Wextra -Werror

.c.o:
		@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(HDRS)
			@$(AR) $(NAME) $(OBJS)

all:	$(NAME)
		
re:		clean fclean all

clean:
		@$(RM) $(OBJS)

fclean:	clean
		@$(RM) $(NAME)
.PHONY:
		all clean fclean re