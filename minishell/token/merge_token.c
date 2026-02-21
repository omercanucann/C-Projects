/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:21 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:22 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	check_type(t_token *current)
{
	if (current->type == HEREDOC_EXIT && current->next
		&& (current->next->type == D_WORD
			|| current->next->type == S_WORD))
		current->type = NE_HEREDOC_EXIT;
}

void	merge_tokens(t_data *data)
{
	t_token	*current;
	t_token	*next;
	char	*merged_content;

	current = data->token;
	while (current && current->next)
	{
		if (current->merge == 1 && current->type != PIPE
			&& current->next->type != PIPE)
		{
			check_type(current);
			next = current->next;
			merged_content = ft_strjoin(current->back_up, next->back_up);
			free(current->back_up);
			current->back_up = merged_content;
			current->merge = next->merge;
			current->next = next->next;
			if (next->next)
				next->next->prev = current;
			free(next->back_up);
			free(next);
			continue ;
		}
		current = current->next;
	}
}
