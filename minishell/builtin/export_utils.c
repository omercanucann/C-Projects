/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesimsek <sesimsek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:57:42 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 18:17:48 by sesimsek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str, t_data *data)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
	{
		data->exit_status = 1;
		return (0);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			data->exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	compare_env(const void *a, const void *b)
{
	t_env_list	*env1;
	t_env_list	*env2;

	env1 = *(t_env_list **)a;
	env2 = *(t_env_list **)b;
	return (ft_strcmp(env1->key, env2->key));
}

int	env_list_size(t_env_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

t_env_list	**env_list_to_array(t_env_list *list, int count)
{
	t_env_list	**array;
	int			i;

	array = malloc(sizeof(t_env_list *) * count);
	if (!array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		array[i] = list;
		list = list->next;
		i++;
	}
	return (array);
}

void	print_sorted_env(t_env_list **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (array[i]->value)
			printf("declare -x %s=\"%s\"\n",
				array[i]->key, array[i]->value);
		else
			printf("declare -x %s\n", array[i]->key);
		i++;
	}
}
