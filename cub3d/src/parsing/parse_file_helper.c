/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:56 by oucan             #+#    #+#             */
/*   Updated: 2025/12/03 19:10:19 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	helper(char **temp, char *line, char **lines, int count)
{
	int	i;

	if (!temp)
	{
		free(line);
		free_split(lines);
		return (1);
	}
	i = 0;
	if (lines)
	{
		while (i < count)
		{
			temp[i] = lines[i];
			i++;
		}
		free(lines);
	}
	return (0);
}

int	get_map_width(char **grid)
{
	int	max_width;
	int	width;
	int	y;

	max_width = 0;
	y = 0;
	while (grid[y])
	{
		width = ft_strlen(grid[y]);
		if (width > max_width)
			max_width = width;
		y++;
	}
	return (max_width);
}

char	get_ext_char(t_map *map, int y, int x, t_bounds *b)
{
	int	row;
	int	col;

	row = y - 1;
	col = x - 1;
	if (row < 0 || col < 0)
		return (' ');
	if (row >= b->height || col >= b->width)
		return (' ');
	if (!map->grid[row])
		return (' ');
	if (col >= (int)ft_strlen(map->grid[row]))
		return (' ');
	return (map->grid[row][col]);
}

int	count_components(t_map *map, int height, int width)
{
	t_flood	f;
	int		c;

	f.height = height;
	f.width = width;
	f.visited = ft_calloc(height * width, sizeof(char));
	if (!f.visited)
		return (-1);
	c = count_loop(map, &f, height, width);
	free(f.visited);
	return (c);
}

int	check_single_component(t_map *map, int height, int width)
{
	int	components;

	components = count_components(map, height, width);
	if (components == -1)
		return (return_error("Memory allocation failed"));
	if (components > 1)
		return (return_error("Map has disconnected parts"));
	return (1);
}
