/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:35:13 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 20:35:14 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_empty_input(t_data *data)
{
	char	*trimmed;

	if (data->input[0] == '\0')
		return (1);
	trimmed = ft_strtrim(data->input, " \t\n\r");
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		free(data->input);
		return (1);
	}
	free(trimmed);
	return (0);
}

static int	check_exit_command(t_data *data)
{
	if (ft_strcmp(data->input, "exit") == 0)
	{
		free(data->input);
		printf("exit\n");
		return (1);
	}
	return (0);
}

static	int	process_tokens(t_data *data, int token_result)
{
	token_result = token_checker(&data->token);
	if (token_result == 0)
	{
		set_var(data);
		merge_tokens(data);
		set_token_type(data->token);
		remove_empty_backup_tokens(data);
		set_command(data);
		data->head_cmd = data->cmd;
		token_result = execute_heredoc(data);
	}
	else
	{
		data->exit_status = 2;
		data->cmd = NULL;
		data->head_cmd = NULL;
	}
	return (token_result);
}

static void	process_input(t_data *data)
{
	int	token_result;

	setup_execution_signals();
	token_result = tokenization(data, data->input);
	if (token_result == 0)
	{
		token_result = process_tokens(data, token_result);
		if (token_result == 0)
			execute_commands(data);
	}
	else
	{
		data->exit_status = 2;
	}
	setup_signals();
	free_data(data);
}

void	interactive(t_data *data, char **env)
{
	int	signal_num;

	if (!data->env)
		init_env_data(data, env);
	setup_signals();
	while (1)
	{
		data->token = NULL;
		signal_num = check_signal();
		if (signal_num == SIGINT)
			data->exit_status = 130;
		data->input = save_history(*data);
		if (!data->input)
			break ;
		if (check_empty_input(data))
			continue ;
		if (check_exit_command(data))
			break ;
		if (data->input)
			process_input(data);
		if (access(".heredoc_temp", F_OK) == 0)
			unlink(".heredoc_temp");
	}
	if (data->env)
		clear_env(data);
}
