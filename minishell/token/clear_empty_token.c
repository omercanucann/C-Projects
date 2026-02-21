/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_empty_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:13 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:14 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empty_backup_tokens(t_data *data)
{
	t_token	*current;
	t_token	*next_token;

	current = data->token;
	while (current)
	{
		next_token = current->next;
		if (current->back_up && current->type == VAR
			&& current->back_up[0] == '\0')
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				data->token = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current->back_up)
				free(current->back_up);
			free(current);
		}
		current = next_token;
	}
}
