/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:56:05 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 20:01:23 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_env_pointers(t_env_list **a, t_env_list **b)
{
	t_env_list	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	compare_env_keys(const char *key1, const char *key2)
{
	int	i;

	i = 0;
	while (key1[i] && key2[i])
	{
		if (key1[i] < key2[i])
			return (-1);
		else if (key1[i] > key2[i])
			return (1);
		i++;
	}
	if (key1[i] == '\0' && key2[i] != '\0')
		return (-1);
	else if (key1[i] != '\0' && key2[i] == '\0')
		return (1);
	return (0);
}

static void	sort_env_array(t_env_list **env_array, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (compare_env_keys(env_array[j]->key, env_array[j + 1]->key) > 0)
				swap_env_pointers(&env_array[j], &env_array[j + 1]);
			j++;
		}
		i++;
	}
}

void	print_env_sorted(t_env *env)
{
	t_env_list	**env_array;
	int			count;

	count = env_list_size(env->env_list);
	env_array = env_list_to_array(env->env_list, count);
	if (!env_array)
		return ;
	sort_env_array(env_array, count);
	print_sorted_env(env_array, count);
	free(env_array);
}
