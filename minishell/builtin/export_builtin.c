/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:44:14 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:44:15 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		free(env[i++]);
	free(env);
}

void	update_minishell_env_from_list(t_env *env)
{
	t_env_list	*tmp;
	char		**new_env;
	int			i;

	free_env_array(env->minishell_env);
	new_env = malloc(sizeof(char *) * (env_list_size(env->env_list) + 1));
	if (!new_env)
		return ;
	tmp = env->env_list;
	i = 0;
	while (tmp)
	{
		new_env[i++] = create_env_entry(tmp);
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	env->minishell_env = new_env;
}

void	update_or_add_env(t_env *env, const char *str)
{
	char		*key;
	char		*value;
	t_env_list	*tmp;

	key = get_key(str);
	value = get_value(str);
	tmp = env->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = value;
			}
			free(key);
			update_minishell_env_from_list(env);
			return ;
		}
		tmp = tmp->next;
	}
	update_helper(env, key, value);
	update_minishell_env_from_list(env);
}

int	export_builtin(t_data *data)
{
	int	i;

	i = 1;
	if (!data->cmd->arguments[1])
	{
		print_env_sorted(data->env);
		return (1);
	}
	while (data->cmd->arguments[i])
	{
		if (is_valid_identifier(data->cmd->arguments[i], data) == 0)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(data->cmd->arguments[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
			i++;
		}
		update_or_add_env(data->env, data->cmd->arguments[i]);
		i++;
	}
	return (0);
}
