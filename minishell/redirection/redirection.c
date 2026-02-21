/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:02:47 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 20:02:48 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	handle_output_file(char *filename, int flags, t_data *data)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror(filename);
		data->exit_status = 1;
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static	void	handle_input_file(char *filename, t_data *data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		data->exit_status = 1;
		cleanup_child_process(data, NULL);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	apply_redirections(t_token *token, t_data *data)
{
	t_token	*current;

	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == HEREDOC_EXIT || current->type == NE_HEREDOC_EXIT)
			handle_input_file(".heredoc_temp", data);
		if (current->type == INPUT_FILE)
			handle_input_file(current->back_up, data);
		else if (current->type == OUTPUT_FILE)
			handle_output_file(current->back_up, O_WRONLY | O_CREAT | O_TRUNC,
				data);
		else if (current->type == APPEND_FILE)
			handle_output_file(current->back_up, O_WRONLY | O_CREAT | O_APPEND,
				data);
		current = current->next;
	}
}

void	handle_redirect_only(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		data->exit_status = 1;
	}
	else if (pid == 0)
	{
		apply_redirections(data->token, data);
		cleanup_child_process(data, NULL);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}
