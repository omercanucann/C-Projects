/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:18 by oucan             #+#    #+#             */
/*   Updated: 2025/12/03 19:07:36 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	outside_cell_invalid(t_map *map, t_flood *f, int y, int x)
{
	int	ext;

	ext = f->width + 2;
	if (ft_strchr("0NSEW", map->grid[y][x])
		&& f->visited[(y + 1) * ext + (x + 1)])
		return (1);
	return (0);
}

static int	check_cell_outside_reach(t_map *map, t_flood *f, int y, int x)
{
	int	ext;

	ext = f->width + 2;
	if (ft_strchr("0NSEW", map->grid[y][x])
		&& f->visited[(y + 1) * ext + (x + 1)])
		return (1);
	return (0);
}

static int	validate_cells(t_map *map, t_flood *f, int height)
{
	int	y;
	int	x;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (map->grid[y] && map->grid[y][++x])
		{
			if (check_cell_outside_reach(map, f, y, x))
			{
				free(f->visited);
				return (return_error("Map is not closed"));
			}
		}
	}
	return (1);
}

int	check_outside_reach(t_map *map, int height, int width)
{
	t_flood	f;
	int		size;
	int		result;

	size = (height + 2) * (width + 2);
	f.visited = ft_calloc(size, sizeof(char));
	if (!f.visited)
		return (return_error("Memory allocation failed"));
	f.height = height;
	f.width = width;
	flood_outside(map, 0, 0, &f);
	result = validate_cells(map, &f, height);
	if (result)
		free(f.visited);
	return (result);
}

int	check_walls_closed(t_map *map)
{
	int	height;
	int	width;

	if (!map || !map->grid)
		return (return_error("Map not initialized"));
	height = get_map_height_from_grid(map->grid);
	width = get_map_width(map->grid);
	if (height == 0 || width == 0)
		return (return_error("Empty map"));
	if (!check_single_component(map, height, width))
		return (0);
	if (!check_outside_reach(map, height, width))
		return (0);
	return (1);
}
