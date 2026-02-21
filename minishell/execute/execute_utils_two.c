/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:33:05 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:36:10 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent(int *prev_fd, int pipe_fd[2], t_command *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	check_directory_access(t_data *data, char *path)
{
	struct stat	path_stat;

	if ((access(path, F_OK) == 0)
		&& (data->cmd->arguments[0][0] == '.'
		|| data->cmd->arguments[0][0] == '/')
		&& (ft_strcmp(data->cmd->arguments[0], "./minishell") != 0))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->arguments[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		cleanup_child_process(data, path);
		exit(126);
	}
	if (stat(path, &path_stat) == 0
		&& S_ISDIR(path_stat.st_mode) && (data->cmd->arguments[0][0] != '.'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_child_process(data, path);
		exit(127);
	}
}

void	handle_file_helper(t_data *data, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd->arguments[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	cleanup_child_process(data, path);
	exit(126);
}

void	check_child_exit_code(int status, t_data *data)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 19);
			data->exit_status = 131;
		}
		else if (sig == SIGINT)
		{
			write(1, "\n", 1);
			data->exit_status = 130;
		}
		else
		{
			data->exit_status = 128 + sig;
		}
	}
	else
	{
		data->exit_status = WEXITSTATUS(status);
	}
}
