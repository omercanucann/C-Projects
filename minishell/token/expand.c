/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:18 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:19 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*create_new_result(char *result, int before_len, int end,
								char *expanded_value)
{
	char	*before;
	char	*after;
	char	*temp1;
	char	*temp_result;

	before = ft_substr(result, 0, before_len);
	if (!before)
		return (NULL);
	after = ft_strdup(result + end);
	if (!after)
		return (free(before), NULL);
	temp1 = ft_strjoin(before, expanded_value);
	if (!temp1)
		return (free(before), free(after), NULL);
	temp_result = ft_strjoin(temp1, after);
	free(before);
	free(after);
	free(temp1);
	return (temp_result);
}

static	char	*process_dollar_sign(char *result, int *i, t_env *env,
		t_data *data)
{
	char	*expanded_value;
	char	*temp_result;
	int		before_len;
	int		expanded_len;

	before_len = *i;
	expanded_value = get_expanded_value(result, i, env, data);
	if (!expanded_value)
		return (result);
	expanded_len = ft_strlen(expanded_value);
	temp_result = create_new_result(result, before_len, *i, expanded_value);
	free(expanded_value);
	if (!temp_result)
		return (result);
	free(result);
	*i = before_len + expanded_len;
	return (temp_result);
}

char	*expanded_var(char *result, t_env *env, t_data *data)
{
	char	*temp_result;
	int		i;

	if (!result || !env)
		return (ft_strdup(""));
	result = ft_strdup(result);
	i = 0;
	while (result[i] != '\0')
	{
		if (result[i] == '$')
		{
			temp_result = process_dollar_sign(result, &i, env, data);
			result = temp_result;
		}
		else
			i++;
	}
	return (result);
}

void	set_var(t_data *data)
{
	t_token	*temp_token;
	char	*temp_back_up;

	temp_token = data->token;
	while (temp_token)
	{
		if (temp_token->prev && temp_token->prev->type == HEREDOC
			&& temp_token->type == WORD)
			temp_token->type = HEREDOC_EXIT;
		if (temp_token->prev && temp_token->prev->type == HEREDOC
			&& temp_token->type == D_WORD)
			temp_token->type = NE_HEREDOC_EXIT;
		if (temp_token->prev && temp_token->prev->type == HEREDOC
			&& temp_token->type == S_WORD)
			temp_token->type = NE_HEREDOC_EXIT;
		if (temp_token->type == VAR || temp_token->type == D_VAR)
		{
			temp_back_up = expanded_var(temp_token->back_up, data->env, data);
			free(temp_token->back_up);
			temp_token->back_up = temp_back_up;
		}
		temp_token = temp_token->next;
	}
}
