/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:44:31 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:59:02 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_strndup(str, i));
}

char	*get_value(const char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

void	update_helper(t_env *env, char *key, char *value)
{
	t_env_list	*new;
	t_env_list	*tmp;

	new = malloc(sizeof(t_env_list));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!env->env_list)
		env->env_list = new;
	else
	{
		tmp = env->env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*create_env_entry(t_env_list *node)
{
	char	*entry;
	char	*temp;

	if (node->value)
	{
		temp = ft_strjoin(node->key, "=");
		if (!temp)
			return (NULL);
		entry = ft_strjoin(temp, node->value);
		free(temp);
	}
	else
	{
		entry = ft_strdup(node->key);
	}
	return (entry);
}
