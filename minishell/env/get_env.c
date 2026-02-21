/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:02:27 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 20:02:28 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *my_env)
{
	t_env_list	*current;
	t_env_list	*next;
	int			i;

	i = 0;
	if (my_env->minishell_env)
	{
		while (my_env->minishell_env[i])
		{
			free(my_env->minishell_env[i]);
			i++;
		}
		free(my_env->minishell_env);
	}
	current = my_env->env_list;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	my_env->minishell_env = NULL;
	my_env->env_list = NULL;
}

void	get_env(t_env *my_env)
{
	int	i;
	int	count;

	count = 0;
	while (my_env->system_envp[count])
		count++;
	my_env->minishell_env = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		my_env->minishell_env[i] = ft_strdup(my_env->system_envp[i]);
		i++;
	}
	my_env->minishell_env[i] = NULL;
}

t_env_list	*create_envlist_node(char *env_line)
{
	t_env_list	*node;
	char		*equal_sign;
	size_t		key_len;

	node = malloc(sizeof(t_env_list));
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(env_line, '=');
	if (!equal_sign)
	{
		free(node);
		return (NULL);
	}
	key_len = equal_sign - env_line;
	node->key = ft_strndup(env_line, key_len);
	node->value = ft_strdup(equal_sign + 1);
	node->next = NULL;
	return (node);
}

void	get_key_and_value(t_env *my_env)
{
	int			i;
	t_env_list	*current;
	t_env_list	*new_node;

	i = 0;
	current = NULL;
	while (my_env->minishell_env[i])
	{
		new_node = create_envlist_node(my_env->minishell_env[i]);
		if (!new_node)
			return ;
		if (!my_env->env_list)
		{
			my_env->env_list = new_node;
			current = my_env->env_list;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
		i++;
	}
}

void	init_env_data(t_data *data, char **env)
{
	data->env = malloc(sizeof(t_env));
	if (!data->env)
	{
		perror("Failed to allocate memory for data.env");
		exit(EXIT_FAILURE);
	}
	data->env->minishell_env = NULL;
	data->env->env_list = NULL;
	data->env->system_envp = env;
	get_env(data->env);
	get_key_and_value(data->env);
}
