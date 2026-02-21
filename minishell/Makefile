# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oucan <oucan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 13:31:19 by oucan             #+#    #+#              #
#    Updated: 2025/07/22 13:31:20 by oucan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses

SRCS = main.c interactive.c utils/ft_strncpy.c token/checker.c token/save_sep.c token/set_command.c heredoc/heredoc.c heredoc/heredoc_utils.c\
        token/token_utils.c token/tokenization.c signal/signal.c history.c utils/free_data.c env/get_env.c execute/execute_pipeline.c \
		builtin/cd_builtin.c execute/execute.c builtin/echo_builtin.c builtin/env_builtin.c builtin/export_builtin.c utils/ft_strcmp.c builtin/export_utils_three.c \
		builtin/pwd_builtin.c builtin/unset_builtin.c  builtin/export_utils.c builtin/export_utils_two.c builtin/exit_builtin.c execute/execute_handle.c utils/ft_strcpy.c utils/ft_strcat.c \
		execute/execute_utils.c execute/execute_utils_two.c execute/get_path.c redirection/redirection.c token/expand.c utils/ft_strndup.c signal/signal_utils.c \
		token/clear_empty_token.c token/expand_utils.c token/merge_token.c token/set_command_utils.c heredoc/heredoc_process.c token/token_utils_2.c token/word_save.c utils/free_data_utils.c
		
OBJS = $(SRCS:.c=.o)
INC = minishell.h
NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME) 

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re