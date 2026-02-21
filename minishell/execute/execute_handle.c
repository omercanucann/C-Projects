/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:29:26 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:36:52 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_path_errors_isdir(t_data *data, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd->arguments[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	cleanup_child_process(data, path);
	exit(126);
}

static void	handle_path_errors_utils(t_data *data, char *path)
{
	struct stat	path_stat;

	if (stat(data->cmd->arguments[0], &path_stat) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->arguments[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		cleanup_child_process(data, path);
		exit(127);
	}
	if (S_ISDIR(path_stat.st_mode))
		handle_path_errors_isdir(data, path);
	if (access(data->cmd->arguments[0], X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->arguments[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		cleanup_child_process(data, path);
		exit(126);
	}
}

void	handle_path_errors(t_data *data, char *path)
{
	if (data->cmd->arguments[0][0] == '/' ||
		(data->cmd->arguments[0][0] == '.' &&
		data->cmd->arguments[0][1] == '/'))
	{
		handle_path_errors_utils(data, path);
	}
	ft_putstr_fd(data->cmd->arguments[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	cleanup_child_process(data, path);
	exit(127);
}

static void	handle_file_path_errors_utils(t_data *data, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd->arguments[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	cleanup_child_process(data, path);
	exit(127);
}

void	handle_file_path_errors(t_data *data, char *path)
{
	struct stat	path_stat;

	if (data->cmd->arguments[0][0] == '/'
		|| (data->cmd->arguments[0][0] == '.'
			&& data->cmd->arguments[0][1] == '/'))
	{
		if (stat(data->cmd->arguments[0], &path_stat) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(data->cmd->arguments[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			cleanup_child_process(data, path);
			exit(127);
		}
		if (S_ISDIR(path_stat.st_mode))
			handle_path_errors_isdir(data, path);
		if (access(data->cmd->arguments[0], X_OK) == -1)
			handle_file_helper(data, path);
	}
	handle_file_path_errors_utils(data, path);
}
