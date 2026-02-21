/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:33:56 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:28:59 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	setup_pipeline_fds(int prev_fd, t_command *cmd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

static void	execute_command(t_data *data, char *path)
{
	execve(path, data->cmd->arguments, data->env->minishell_env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd->arguments[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	cleanup_child_process(data, path);
	exit(126);
}

static void	exec_child(t_data *data, t_command *cmd,
						int prev_fd, int pipe_fd[2])
{
	char	*path;
	int		status;

	setup_child_signals();
	setup_pipeline_fds(prev_fd, cmd, pipe_fd);
	apply_redirections(cmd->tokens, data);
	data->cmd = cmd;
	if (!cmd->command && cmd->tokens)
	{
		cleanup_child_process(data, NULL);
		exit(1);
	}
	else if (is_builtin(data))
	{
		status = execute_builtin(data);
		cleanup_child_process(data, NULL);
		exit(status);
	}
	path = find_path(data);
	if (!path)
		handle_file_path_errors(data, path);
	if (access(path, X_OK) != 0)
		check_path_permissions(data, path);
	execute_command(data, path);
}

static int	process_command(t_data *data, t_command *cmd, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (cmd->next && pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		exec_child(data, cmd, *prev_fd, pipe_fd);
	handle_parent(prev_fd, pipe_fd, cmd);
	return (pid);
}

int	execute_pipeline(t_data *data)
{
	t_command	*cmd;
	int			prev_fd;
	int			status;
	pid_t		last_pid;
	int			result;

	cmd = data->cmd;
	prev_fd = -1;
	last_pid = -1;
	while (cmd)
	{
		result = process_command(data, cmd, &prev_fd);
		if (result == 0)
			return (0);
		if (result == 1)
			return (1);
		last_pid = result;
		cmd = cmd->next;
	}
	waitpid(last_pid, &status, 0);
	check_child_exit_code(status, data);
	while (wait(NULL) > 0)
		;
	return (data->exit_status);
}
