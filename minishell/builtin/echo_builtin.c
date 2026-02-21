/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:57 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:38:58 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	n_flag(t_flag *flag, char **args)
{
	int	j;

	while (args[flag->i] && args[flag->i][0] == '-' && args[flag->i][1] == 'n')
	{
		j = 1;
		while (args[flag->i][j] == 'n')
			j++;
		if (args[flag->i][j] == '\0')
		{
			flag->new_line = 0;
			flag->i++;
		}
		else
			break ;
	}
}

int	echo_builtin(char **args)
{
	t_flag	*flag;

	flag = malloc(sizeof(t_flag));
	if (!flag)
		return (perror("malloc failed"), 0);
	flag->i = 1;
	flag->new_line = 1;
	n_flag(flag, args);
	while (args[flag->i])
	{
		if (!args[flag->i])
			return (ft_putchar_fd('\n', 1), 0);
		ft_putstr_fd(args[flag->i], 1);
		if (args[flag->i + 1])
			ft_putchar_fd(' ', 1);
		flag->i++;
	}
	if (flag->new_line)
		ft_putchar_fd('\n', 1);
	return (free(flag), 0);
}

int	execute_echo_builtin(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		apply_redirections(data->token, data);
		status = execute_builtin(data);
		cleanup_child_process(data, NULL);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		data->exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
}
