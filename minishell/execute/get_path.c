/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:34:22 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 20:57:25 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_data *data, char *str)
{
	t_env_list	*tmp;

	tmp = data->env->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*join_path(const char *dir, const char *cmd)
{
	size_t	len_dir;
	size_t	len_cmd;
	size_t	total_len;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	total_len = len_dir + 1 + len_cmd + 1;
	full = malloc(total_len);
	if (!full)
		return (NULL);
	ft_strcpy(full, dir);
	if (dir[len_dir - 1] != '/')
		ft_strcat(full, "/");
	ft_strcat(full, cmd);
	return (full);
}

static char	*check_direct_path(char *path)
{
	if (path[0] == '\0')
		return (NULL);
	if (ft_strchr(path, '/') && access(path, X_OK) == 0)
		return (ft_strdup(path));
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path)
			continue ;
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

char	*find_path(t_data *data)
{
	char	*path;
	char	*path_env;
	char	**paths;
	char	*result;

	path = data->cmd->arguments[0];
	result = check_direct_path(path);
	if (result)
		return (result);
	path_env = get_env_value(data, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, path);
	free_split_array(paths);
	return (result);
}
