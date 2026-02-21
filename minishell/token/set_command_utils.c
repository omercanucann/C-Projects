/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:25 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:26 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*copy_token(t_token *src)
{
	t_token	*new_token;

	if (!src)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = src->type;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (src->back_up)
		new_token->back_up = ft_strdup(src->back_up);
	else
		new_token->back_up = NULL;
	return (new_token);
}

void	add_token_to_cmd(t_token **token_list, t_token *new_token)
{
	t_token	*current;

	if (!token_list || !new_token)
		return ;
	if (*token_list == NULL)
	{
		*token_list = new_token;
		return ;
	}
	current = *token_list;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	fill_arguments(t_command *new_cmd,
								t_token *start_token, int arg_count)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = start_token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == S_WORD || tmp->type == D_WORD
			|| tmp->type == S_VAR || tmp->type == VAR || tmp->type == D_VAR)
		{
			if (!(tmp->type == VAR && tmp->back_up && tmp->back_up[0] == '\0'))
			{
				new_cmd->arguments[i] = ft_strdup(tmp->back_up);
				i++;
			}
		}
		tmp = tmp->next;
	}
	new_cmd->arguments[i] = NULL;
	if (arg_count > 0)
		new_cmd->command = ft_strdup(new_cmd->arguments[0]);
}
