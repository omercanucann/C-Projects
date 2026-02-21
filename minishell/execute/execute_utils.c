/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:34:06 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:34:07 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_data *data)
{
	int	r;

	if (ft_strncmp(data->cmd->arguments[0], "cd", 3) == 0)
		r = cd_builtin(data);
	if (ft_strncmp(data->cmd->arguments[0], "echo", 5) == 0)
		r = echo_builtin(data->cmd->arguments);
	if (ft_strncmp(data->cmd->arguments[0], "env", 4) == 0)
		r = env_builtin(data);
	if (ft_strncmp(data->cmd->arguments[0], "export", 7) == 0)
		r = export_builtin(data);
	if (ft_strncmp(data->cmd->arguments[0], "pwd", 4) == 0)
		r = pwd_builtin();
	if (ft_strncmp(data->cmd->arguments[0], "unset", 6) == 0)
		r = unset_builtin(data);
	if (ft_strncmp(data->cmd->arguments[0], "exit", 5) == 0)
		r = exit_builtin(data, data->cmd->arguments);
	return (r);
}

bool	is_builtin(t_data *data)
{
	if (ft_strncmp(data->cmd->arguments[0], "cd", 3) == 0)
		return (true);
	if (ft_strncmp(data->cmd->arguments[0], "echo", 5) == 0)
		return (true);
	if (ft_strncmp(data->cmd->arguments[0], "env", 4) == 0)
		return (true);
	if (ft_strncmp(data->cmd->arguments[0], "export", 7) == 0)
		return (true);
	if (ft_strncmp(data->cmd->arguments[0], "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(data->cmd->arguments[0], "unset", 6) == 0)
		return (true);
	if (ft_strncmp(data->cmd->arguments[0], "exit", 5) == 0)
		return (true);
	return (false);
}
