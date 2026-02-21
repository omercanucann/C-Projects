/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tissue_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:17:57 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 19:20:13 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*extract_and_validate_path(char *line)
{
	char	*path;

	path = extract_path(line);
	if (!path || !validate_texture_path(path))
	{
		free(path);
		return (NULL);
	}
	return (path);
}

int	set_ns_texture(char *line, t_map *map, char *path)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map->north_texture)
			return (0);
		map->north_texture = path;
		return (1);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->south_texture)
			return (0);
		map->south_texture = path;
		return (1);
	}
	return (0);
}

int	set_we_texture(char *line, t_map *map, char *path)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map->west_texture)
			return (0);
		map->west_texture = path;
		return (1);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map->east_texture)
			return (0);
		map->east_texture = path;
		return (1);
	}
	return (0);
}

int	set_texture_by_prefix(char *line, t_map *map, char *path)
{
	if (set_ns_texture(line, map, path))
		return (1);
	if (set_we_texture(line, map, path))
		return (1);
	return (0);
}
