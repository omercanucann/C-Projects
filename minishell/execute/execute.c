/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:33:48 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:28:45 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path_permissions(t_data *data, char *path)
{
	struct stat	path_stat;

	if ((access(path, F_OK) == 0)
		&& (data->cmd->arguments[0][0] == '.'
		|| data->cmd->arguments[0][0] == '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->arguments[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		cleanup_child_process(data, path);
		exit(126);
	}
	if (stat(path, &path_stat) == 0
		&& S_ISDIR(path_stat.st_mode)
		&& (data->cmd->arguments[0][0] != '.'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_child_process(data, path);
		exit(127);
	}
}

static void	execute_external_command(t_data *data)
{
	char	*path;

	apply_redirections(data->token, data);
	path = find_path(data);
	if (!path)
		handle_path_errors(data, path);
	if (access(path, X_OK) != 0)
		check_directory_access(data, path);
	execve(path, data->cmd->arguments, data->env->minishell_env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd->arguments[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	cleanup_child_process(data, path);
	exit(126);
}

static	int	handle_external_command(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		execute_external_command(data);
		return (127);
	}
	else
	{
		waitpid(pid, &status, 0);
		check_child_exit_code(status, data);
		return (data->exit_status);
	}
	return (0);
}

int	execute(t_data *data)
{
	int	source_in;
	int	source_out;

	source_in = dup(STDIN_FILENO);
	source_out = dup(STDOUT_FILENO);
	if (is_builtin(data))
	{
		if (ft_strcmp(data->cmd->arguments[0], "echo") == 0)
			return (execute_echo_builtin(data));
		else
		{
			apply_redirections(data->token, data);
			execute_builtin(data);
			dup2(source_in, STDIN_FILENO);
			dup2(source_out, STDOUT_FILENO);
			return (0);
		}
	}
	else
		return (handle_external_command(data));
}

void	execute_commands(t_data *data)
{
	if (!data->cmd || !data->cmd->arguments || !data->cmd->arguments[0])
		handle_redirect_only(data);
	else
	{
		if (data->cmd->next)
			execute_pipeline(data);
		else
			execute(data);
	}
}
