/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:29:15 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:29:16 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	handle_child_exit(int status, int temp_fd, t_data *data)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		data->exit_status = 130;
		unlink(".heredoc_temp");
		close(temp_fd);
		signal(SIGINT, simple_signal_handler);
		return (1);
	}
	close(temp_fd);
	signal(SIGINT, simple_signal_handler);
	return (0);
}

int	read_heredoc(char *delimiter, int type, t_env *env, t_data *data)
{
	int		temp_fd;
	int		status;
	pid_t	pid;

	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
		return (1);
	pid = fork();
	if (pid == 0)
		heredoc_child_process(delimiter, type, env, temp_fd);
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		return (handle_child_exit(status, temp_fd, data));
	}
	else
	{
		perror("fork");
		close(temp_fd);
		return (1);
	}
	return (0);
}

int	execute_heredoc(t_data *data)
{
	t_token	*temp;
	int		status;

	status = 0;
	set_data(data);
	temp = data->token;
	while (temp)
	{
		if (temp->type == HEREDOC)
		{
			status = read_heredoc(temp->next->back_up, temp->next->type,
					data->env, data);
			if (status == 1)
				return (status);
		}
		temp = temp->next;
	}
	return (status);
}
