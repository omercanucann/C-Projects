/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:33 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:34 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	set_redirect_types(t_token *runner)
{
	if (runner->type == TRUNC)
		runner->next->type = OUTPUT_FILE;
	else if (runner->type == APPEND)
		runner->next->type = APPEND_FILE;
	else if (runner->type == INPUT)
		runner->next->type = INPUT_FILE;
}

static	void	process_segment(t_token *segment_start)
{
	t_token	*runner;

	runner = segment_start;
	while (runner && runner->type != PIPE)
	{
		if (runner->next)
			set_redirect_types(runner);
		runner = runner->next;
	}
}

void	set_token_type(t_token *token)
{
	t_token	*segment_start;
	t_token	*runner;

	segment_start = token;
	while (segment_start)
	{
		process_segment(segment_start);
		runner = segment_start;
		while (runner && runner->type != PIPE)
			runner = runner->next;
		if (runner && runner->type == PIPE)
			segment_start = runner->next;
		else
			segment_start = NULL;
	}
}

void	add_back_token(t_token **token, t_token *new_token)
{
	t_token	*start;

	start = *token;
	if (start == NULL)
	{
		*token = new_token;
		return ;
	}
	if (*token)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_token;
		new_token->prev = start;
	}
}
