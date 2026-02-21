/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:35:24 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 20:35:25 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_token
{
	char			*back_up;
	int				type;
	int				merge;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	struct s_command	*next;
	struct s_command	*prev;
	t_token				*tokens;
}	t_command;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_env
{
	char		**system_envp;
	char		**minishell_env;
	t_env_list	*env_list;
}	t_env;

typedef struct s_data
{
	t_token		*token;
	bool		interactive;
	char		*input;
	t_env		*env;
	t_command	*cmd;
	t_command	*head_cmd;
	int			exit_status;
}	t_data;

typedef struct s_flag
{
	int	i;
	int	new_line;
}	t_flag;

enum e_token_type
{
	SPACES,
	PIPE,
	INPUT,
	TRUNC,
	APPEND,
	END,
	HEREDOC,
	WORD,
	S_WORD,
	D_WORD,
	S_VAR,
	D_VAR,
	VAR,
	HEREDOC_EXIT,
	NE_HEREDOC_EXIT,
	INPUT_FILE,
	OUTPUT_FILE,
	APPEND_FILE,
};

enum e_nail_status
{
	DEFAULT,
	SNAIL,
	DNAIL
};

char		*expanded_var(char *result, t_env *env, t_data *data);
t_data		*get_data(void);
void		read_heredoc_helper(char *delimiter, int temp_fd,
				t_env *env, int type);
void		heredoc_child_process(char *delimiter,
				int type, t_env *env, int fd);
void		read_heredoc_child(char *delimiter,
				int type, t_env *env, int temp_fd);
void		set_data(t_data *data);
void		handle_print_line(char *line, int temp_fd);
void		handle_path_errors(t_data *data, char *path);
int			ft_strcmp(char *s1, char *s2);
void		check_directory_access(t_data *data, char *path);
void		handle_file_helper(t_data *data, char *path);
void		handle_file_path_errors(t_data *data, char *path);
void		check_path_permissions(t_data *data, char *path);
int			execute_echo_builtin(t_data *data);
int			exit_builtin(t_data *data, char **args);
void		cleanup_child_process(t_data *data, char *path);
void		free_split_array(char **array);
void		execute_commands(t_data *data);
void		set_var(t_data *data);
void		merge_tokens(t_data *data);
void		remove_empty_backup_tokens(t_data *data);
void		init_env_data(t_data *data, char **env);
void		handle_redirect_only(t_data *data);
int			read_heredoc(char *delimiter, int type, t_env *env, t_data *data);
void		read_all_heredocs(t_token *token, bool is_last_input_heredoc,
				t_token *last_in_redir, char **heredoc_temp_file);
int			execute_heredoc(t_data *data);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			check_operator_type(char *str);
void		create_token(t_token **token_list, char *word,
				int type, int merge);
void		fill_token(t_token *token, char *word, int type, int merge);
t_token		*copy_token(t_token *src);
void		set_token_type(t_token *token);
void		add_back_token(t_token **token, t_token *new_token);
void		add_token_to_cmd(t_token **token_list, t_token *new_token);
void		fill_arguments(t_command *new_cmd,
				t_token *start_token, int arg_count);
char		*save_separator(t_token **token_list, char *str, int type);
int			is_word_delimiter(char c);
void		set_command(t_data *data);
int			set_status(int status, char *str);
int			seperator(char *str);
char		*quote_word_save(t_token **token_list, char *str, char q_type);
char		*word_save(t_token **token_list, char *str);
void		free_ptr(void *ptr);
char		*get_expanded_value(char *result, int *i, t_env *env, t_data *data);
void		create_command_node(t_token *start_token, t_data *data);
int			token_checker(t_token **token_list);
void		interactive(t_data *data, char **env);
void		signal_handler(int signo);
void		execution_signal_handler(int signo);
void		simple_signal_handler(int signo);
void		setup_signals(void);
void		setup_execution_signals(void);
void		setup_child_signals(void);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strcpy(char *dest, const char *src);
void		reset_signals(void);
int			check_signal(void);
char		*save_history(t_data data);
int			tokenization(t_data *data, char *str);
void		free_data(t_data *data);
void		check_child_exit_code(int status, t_data *data);
void		get_key_and_value(t_env *my_env);
void		get_env(t_env *my_env);
void		free_env(t_env *my_env);
int			cd_builtin(t_data *data);
int			execute_builtin(t_data *data);
int			echo_builtin(char **args);
int			env_builtin(t_data *data);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(const char *s, size_t n);
int			export_builtin(t_data *data);
int			pwd_builtin(void);
void		clear_env(t_data *data);
int			is_valid_identifier(const char *str, t_data *data);
int			unset_builtin(t_data *data);
void		update_minishell_env_from_list(t_env *env);
void		print_env_variable(t_data *data);
int			execute(t_data *data);
int			execute_pipeline(t_data *data);
void		print_env_variable_two(t_data *data, int i);
void		print_env_sorted(t_env *env);
char		*get_key(const char *str);
char		*get_value(const char *str);
void		update_helper(t_env *env, char *key, char *value);
char		*create_env_entry(t_env_list *node);
int			compare_env(const void *a, const void *b);
int			env_list_size(t_env_list *list);
void		print_sorted_env(t_env_list **array, int count);
t_env_list	**env_list_to_array(t_env_list *list, int count);
bool		is_builtin(t_data *data);
char		*get_env_value(t_data *data, char *str);
char		*join_path(const char *dir, const char *cmd);
char		*find_path(t_data *data);
void		handle_parent(int *prev_fd, int pipe_fd[2], t_command *cmd);
void		apply_redirections(t_token *token, t_data *data);
void		heredoc_sigint_handler(int signo);
#endif