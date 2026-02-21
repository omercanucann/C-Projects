/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:39:12 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:39:13 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->env || !data->env->minishell_env)
		return (0);
	if (data->cmd->arguments[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(data->cmd->arguments[1], 2);
		ft_putstr_fd(": Too many arguments \n", 2);
		return (1);
	}
	while (data->env->minishell_env[i])
	{
		ft_putstr_fd(data->env->minishell_env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
