/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tissue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:16 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 19:18:48 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*extract_path(char *line)
{
	char	*trimmed;
	char	*path;

	trimmed = ft_strtrim_whitespace(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		path = ft_strtrim_whitespace(trimmed + 3);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		path = ft_strtrim_whitespace(trimmed + 3);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		path = ft_strtrim_whitespace(trimmed + 3);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		path = ft_strtrim_whitespace(trimmed + 3);
	else
		path = NULL;
	free(trimmed);
	return (path);
}

int	validate_texture_path(char *path)
{
	int	len;
	int	fd;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	parse_texture_line(char *line, t_map *map)
{
	char	*path;
	int		ok;

	path = extract_and_validate_path(line);
	if (!path)
		return (0);
	ok = set_texture_by_prefix(line, map, path);
	if (!ok)
	{
		free(path);
		return (0);
	}
	return (1);
}

int	load_single_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Texture Failed to Load: %s\n", path);
		return (0);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	return (1);
}
