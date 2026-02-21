/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:11 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:12 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checker_variable(t_token **token_node)
{
	if (!token_node || !(*token_node) || !(*token_node)->back_up)
		return ;
	while (*token_node)
	{
		if ((!(*token_node)->prev || (*token_node)->prev->type != HEREDOC)
			&& ft_strchr((*token_node)->back_up, '$') != 0)
		{
			if ((*token_node)->type == S_WORD)
				(*token_node)->type = S_VAR;
			else if ((*token_node)->type == WORD)
				(*token_node)->type = VAR;
			else if ((*token_node)->type == D_WORD)
				(*token_node)->type = D_VAR;
		}
		*token_node = (*token_node)->next;
	}
}

static	int	check_syntax(int type)
{
	if (type == HEREDOC || type == INPUT || type == APPEND || type == TRUNC)
		return (1);
	return (0);
}

static	int	check_pipe_errors(t_token *temp)
{
	if (temp->type == PIPE && temp->prev && temp->prev->type == PIPE)
	{
		ft_putstr_fd("PIPE ERROR\n", 2);
		return (1);
	}
	if (!temp->next && temp->type == PIPE)
	{
		ft_putstr_fd("PIPE ERROR\n", 2);
		return (1);
	}
	return (0);
}

static	int	check_syntax_errors(t_token *temp)
{
	if (temp->next && check_syntax(temp->type) == 1
		&& check_syntax(temp->next->type) == 1)
	{
		ft_putstr_fd("minishell :syntax error near unexpected token\n", 2);
		return (1);
	}
	if (!temp->next && check_syntax(temp->type) == 1)
	{
		ft_putstr_fd("minishell :syntax error near unexpected token ", 2);
		ft_putstr_fd("`newline'\n", 2);
		return (1);
	}
	return (0);
}

int	token_checker(t_token **token_list)
{
	t_token	*temp;
	t_token	*check_variable;

	check_variable = *token_list;
	temp = *token_list;
	if (temp->type == PIPE)
	{
		ft_putstr_fd("PIPE ERROR\n", 2);
		return (1);
	}
	checker_variable(&check_variable);
	while (temp)
	{
		if (check_syntax_errors(temp))
			return (1);
		if (check_pipe_errors(temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}
