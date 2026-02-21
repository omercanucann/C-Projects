/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:27 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:28 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	count_arguments(t_token *start_token)
{
	int		arg_count;
	t_token	*tmp;

	arg_count = 0;
	tmp = start_token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == S_WORD || tmp->type == D_WORD
			|| tmp->type == S_VAR || tmp->type == VAR || tmp->type == D_VAR)
		{
			if (!(tmp->type == VAR && tmp->back_up && tmp->back_up[0] == '\0'))
				arg_count++;
		}
		tmp = tmp->next;
	}
	return (arg_count);
}

static	void	copy_tokens_to_command(t_command *new_cmd, t_token *start_token)
{
	t_token	*tmp;
	t_token	*token_copy;

	new_cmd->tokens = NULL;
	tmp = start_token;
	while (tmp && tmp->type != PIPE)
	{
		token_copy = copy_token(tmp);
		add_token_to_cmd(&new_cmd->tokens, token_copy);
		tmp = tmp->next;
	}
}

static	void	add_command_to_list(t_data *data, t_command *new_cmd)
{
	t_command	*current;

	if (!data->cmd)
		data->cmd = new_cmd;
	else
	{
		current = data->cmd;
		while (current->next)
			current = current->next;
		current->next = new_cmd;
		new_cmd->prev = current;
	}
}

void	create_command_node(t_token *start_token, t_data *data)
{
	t_command	*new_cmd;
	int			arg_count;

	arg_count = count_arguments(start_token);
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return ;
	ft_bzero(new_cmd, sizeof(t_command));
	new_cmd->arguments = malloc(sizeof(char *) * (arg_count + 1));
	if (!new_cmd->arguments)
	{
		free(new_cmd);
		return ;
	}
	fill_arguments(new_cmd, start_token, arg_count);
	copy_tokens_to_command(new_cmd, start_token);
	add_command_to_list(data, new_cmd);
}

void	set_command(t_data *data)
{
	t_token	*current_token;
	t_token	*command_start;

	if (!data->token)
		return ;
	current_token = data->token;
	command_start = current_token;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			create_command_node(command_start, data);
			command_start = current_token->next;
		}
		current_token = current_token->next;
	}
	if (command_start)
		create_command_node(command_start, data);
}
