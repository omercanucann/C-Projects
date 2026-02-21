/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:57 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:58 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_clear_token(t_token **token, void (*del)(void *))
{
	t_token	*current;
	t_token	*next;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		if (del)
			del(current->back_up);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	list_del_command(t_command *list, void (*del)(void *))
{
	int	i;

	if (!list || !del)
		return ;
	if (list->command)
		(*del)(list->command);
	if (list->arguments)
	{
		i = 0;
		while (list->arguments[i])
		{
			(*del)(list->arguments[i]);
			i++;
		}
		free(list->arguments);
	}
	if (list->tokens)
		list_clear_token(&list->tokens, del);
}

void	list_clear_command(t_command **list, void (*del)(void *))
{
	t_command	*temp;

	if (!list || !*list)
		return ;
	while (*list != NULL)
	{
		temp = (*list)->next;
		list_del_command(*list, del);
		free(*list);
		*list = temp;
	}
}

void	cleanup_child_process(t_data *data, char *path)
{
	data->cmd = data->head_cmd;
	free_data(data);
	if (path)
		free(path);
	if (data->env)
	{
		free_env(data->env);
		free(data->env);
		data->env = NULL;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->cmd)
		data->cmd = data->head_cmd;
	if (data->token)
		list_clear_token(&data->token, &free_ptr);
	if (data->cmd)
		list_clear_command(&data->cmd, &free_ptr);
}
