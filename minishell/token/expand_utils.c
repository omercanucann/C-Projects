/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:16 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:17 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*handle_exit_status(int *i, t_data *data)
{
	char	*expanded_value;

	expanded_value = ft_itoa(data->exit_status);
	*i = *i + 1;
	return (expanded_value);
}

static	char	*find_env_value(char *var_name, t_env *env)
{
	t_env_list	*env_node;
	char		*expanded_value;

	expanded_value = ft_strdup("");
	env_node = env->env_list;
	while (env_node)
	{
		if (ft_strcmp(env_node->key, var_name) == 0)
		{
			free(expanded_value);
			expanded_value = ft_strdup(env_node->value);
			break ;
		}
		env_node = env_node->next;
	}
	return (expanded_value);
}

char	*get_expanded_value(char *result, int *i, t_env *env, t_data *data)
{
	char		*var_name;
	char		*expanded_value;
	int			start;
	int			end;

	(*i)++;
	start = *i;
	if (result[*i] == '?')
		return (handle_exit_status(i, data));
	while (result[*i] && (ft_isalnum(result[*i]) || result[*i] == '_'))
		(*i)++;
	end = *i;
	var_name = ft_substr(result, start, end - start);
	if (!var_name)
		return (ft_strdup(""));
	expanded_value = find_env_value(var_name, env);
	if (var_name[0] == '\0' && result[*i - 1] == '$')
	{
		free(expanded_value);
		expanded_value = ft_strdup("$");
	}
	free(var_name);
	return (expanded_value);
}
