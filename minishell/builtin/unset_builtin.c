/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:00:07 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 20:00:08 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_key(t_env *env, const char *key)
{
	t_env_list	*tmp;
	t_env_list	*prev;

	prev = NULL;
	tmp = env->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, (char *)key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				env->env_list = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset_builtin(t_data *data)
{
	int	i;

	i = 1;
	while (data->cmd->arguments[i])
	{
		if (is_valid_identifier(data->cmd->arguments[i], data) == 0)
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(data->cmd->arguments[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			i++;
			continue ;
		}
		remove_env_key(data->env, data->cmd->arguments[i]);
		i++;
	}
	update_minishell_env_from_list(data->env);
	return (0);
}
