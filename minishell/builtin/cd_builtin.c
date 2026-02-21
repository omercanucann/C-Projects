/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:38:19 by oucan             #+#    #+#             */
/*   Updated: 2025/07/17 19:38:20 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_home(t_data *data)
{
	t_env_list	*var;

	var = data->env->env_list;
	while (var)
	{
		if (ft_strncmp(var->key, "HOME", 5) == 0)
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

char	*get_old_pwd(char *oldpwd, int j, int i)
{
	char	*new_pwd;

	new_pwd = malloc(sizeof(char) * i + 1);
	i = 0;
	while (oldpwd[i])
	{
		if (oldpwd[i] == '/')
			j--;
		if (j == 0)
			break ;
		new_pwd[i] = oldpwd[i];
		i++;
	}
	new_pwd[i] = '\0';
	return (new_pwd);
}

char	*pwd_counter(char *oldpwd)
{
	int		i;
	int		j;
	int		temp_j;
	char	*new_pwd;

	j = 0;
	i = 0;
	while (oldpwd[i])
	{
		if (oldpwd[i] == '/')
			j++;
		i++;
	}
	i = 0;
	temp_j = j;
	while (oldpwd[i])
	{
		if (oldpwd[i] == '/')
			j--;
		if (j == 0)
			break ;
		i++;
	}
	new_pwd = get_old_pwd(oldpwd, temp_j, i);
	return (new_pwd);
}

int	cd_builtin(t_data *data)
{
	char	*target_path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ft_putstr_fd("Old pwd error\n", 2), data->exit_status = 1, 1);
	if (data->cmd->arguments[1] == NULL)
		target_path = cd_home(data);
	else if (data->cmd->arguments[2] != NULL)
		return (free(oldpwd), data->exit_status = 1,
			ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	else if (data->cmd->arguments[1] != NULL)
		target_path = data->cmd->arguments[1];
	else if (data->cmd->arguments[1][0] == '.' &&
				data->cmd->arguments[1][1] == '.' &&
				data->cmd->arguments[1][2] == '\0')
		target_path = pwd_counter(oldpwd);
	if (chdir(target_path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->cmd->arguments[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (free(oldpwd), data->exit_status = 1, 1);
	}
	return (free(oldpwd), 0);
}
