/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:29:22 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:29:23 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	process_heredoc_line(char *line, char *delimiter, int fd)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		close(fd);
		cleanup_child_process(get_data(), NULL);
		exit(0);
	}
}

static	char	*handle_line_expansion(char *line, int type,
			t_env *env, t_data *data)
{
	if (type == HEREDOC_EXIT && ft_strchr(line, '$'))
		line = expanded_var(line, env, data);
	return (line);
}

void	heredoc_child_process(char *delimiter, int type, t_env *env, int fd)
{
	char	*line;
	t_data	*data;

	data = get_data();
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: heredoc delimited by EOF\n", 2);
			close(fd);
			cleanup_child_process(get_data(), NULL);
			exit(0);
		}
		process_heredoc_line(line, delimiter, fd);
		line = handle_line_expansion(line, type, env, data);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}
