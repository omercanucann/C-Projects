/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:35:40 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 20:35:42 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	detail_quotes_command(char *cmd)
{
	return (ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0);
}

bool	ft_is_digit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	error_msg_cmd(const char *command, const char *detail,
		const char *error_message, int error_nb)
{
	bool	detail_quotes;

	detail_quotes = detail_quotes_command((char *)command);
	write(2, "minishell> ", 11);
	if (command)
	{
		write(2, command, strlen(command));
		write(2, ": ", 2);
	}
	if (detail)
	{
		if (detail_quotes)
			write(2, "`", 1);
		write(2, detail, strlen(detail));
		if (detail_quotes)
			write(2, "'", 1);
		write(2, ": ", 2);
	}
	if (error_message)
		write(2, error_message, strlen(error_message));
	write(2, "\n", 1);
	return (error_nb);
}

void	exit_builtin_helper(t_data *data, char **args)
{
	ft_putstr_fd("exit\n", 1);
	error_msg_cmd("exit", args[1], "numeric argument required", 2);
	cleanup_child_process(data, NULL);
	data->exit_status = 2;
	exit(2);
}

int	exit_builtin(t_data *data, char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("exit\n", 1);
		cleanup_child_process(data, NULL);
		data->exit_status = 0;
		exit(data->exit_status);
	}
	if (!ft_is_digit_str(args[1]))
		exit_builtin_helper(data, args);
	if (args[2])
	{
		ft_putstr_fd("exit\n", 1);
		error_msg_cmd("exit", NULL, "too many arguments", 1);
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = ft_atoi(args[1]);
	ft_putstr_fd("exit\n", 1);
	cleanup_child_process(data, NULL);
	exit(data->exit_status);
}
