/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:30 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:31 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator_type(char *str)
{
	if (*str == '|')
		return (PIPE);
	else if (*str == '<' && (*str + 1) == '<')
		return (HEREDOC);
	else if (*str == '>' && (*str + 1) == '>')
		return (APPEND);
	else if (*str == '<')
		return (INPUT);
	else if (*str == '>')
		return (TRUNC);
	else if (*str == '\'')
		return (S_WORD);
	else if (*str == '\"')
		return (D_WORD);
	return (WORD);
}

void	fill_token(t_token *token, char *word, int type, int merge)
{
	token->back_up = ft_strdup(word);
	token->type = type;
	token->merge = merge;
	token->prev = NULL;
	token->next = NULL;
}

int	set_status(int status, char *str)
{
	if (*str == '\'' && status == DEFAULT)
		status = SNAIL;
	else if (*str == '\"' && status == DEFAULT)
		status = DNAIL;
	else if (*str == '\'' && status == SNAIL)
		status = DEFAULT;
	else if (*str == '\"' && status == DNAIL)
		status = DEFAULT;
	return (status);
}

int	seperator(char *str)
{
	if ((*str > 8 && *str < 14) || *str == 32)
		return (SPACES);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '<' && *(str + 1) == '<')
		return (HEREDOC);
	else if (*str == '>' && *(str + 1) == '>')
		return (APPEND);
	else if (*str == '<')
		return (INPUT);
	else if (*str == '>')
		return (TRUNC);
	else if (*str == '\0')
		return (END);
	else
		return (0);
}

int	is_word_delimiter(char c)
{
	if (c == '\0' || c == '\'' || c == '\"' || c == ' '
		|| c == '\t' || c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}
