/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:21 by oucan             #+#    #+#             */
/*   Updated: 2025/12/03 18:58:55 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (ft_isspace(c))
		return (1);
	return (0);
}

int	validate_map(t_game *game)
{
	printf("Map validation...\n");
	if (!check_valid_characters(&game->map))
		return (0);
	printf("✓ All characters are valid\n");
	if (!check_walls_closed(&game->map))
		return (0);
	printf("✓ The map is surrounded by walls\n");
	return (1);
}

int	check_valid_characters(t_map *map)
{
	int	y;
	int	x;

	if (!map || !map->grid)
		return (return_error("Map not initialized"));
	y = -1;
	while (map->grid[++y])
	{
		x = -1;
		while (map->grid[y][++x])
			if (!is_valid_map_char(map->grid[y][x]))
				return (return_error("Map contains invalid character"));
	}
	return (1);
}

int	get_map_height_from_grid(char **grid)
{
	int	h;

	h = 0;
	if (!grid)
		return (0);
	while (grid[h])
		h++;
	return (h);
}

char	get_char(t_map *map, int y, int x)
{
	if (y < 0 || x < 0)
		return (' ');
	if (!map->grid[y])
		return (' ');
	if (x >= (int)ft_strlen(map->grid[y]))
		return (' ');
	return (map->grid[y][x]);
}
