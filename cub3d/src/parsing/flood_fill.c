/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:36 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:45:50 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	**copy_map_grid(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	flood_fill_recursive(char **grid, int x, int y, t_map *map)
{
	if (y < 0 || y >= map->height || x < 0 || x >= (int)ft_strlen(grid[y]))
		return (0);
	if (ft_isspace(grid[y][x]))
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	if (grid[y][x] != '0' && grid[y][x] != 'N' && grid[y][x] != 'S' &&
		grid[y][x] != 'E' && grid[y][x] != 'W')
		return (1);
	grid[y][x] = 'V';
	if (!flood_fill_recursive(grid, x, y - 1, map))
		return (0);
	if (!flood_fill_recursive(grid, x, y + 1, map))
		return (0);
	if (!flood_fill_recursive(grid, x - 1, y, map))
		return (0);
	if (!flood_fill_recursive(grid, x + 1, y, map))
		return (0);
	return (1);
}

static int	find_player_coords(t_map *map, int *player_x, int *player_y)
{
	int	i;
	int	j;

	*player_x = -1;
	*player_y = -1;
	i = 0;
	while (i < map->height && *player_x == -1)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				*player_x = j;
				*player_y = i;
				break ;
			}
			j++;
		}
		i++;
	}
	return (*player_x != -1);
}

static void	free_grid_copy(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

int	flood_fill_check(t_map *map)
{
	char	**grid_copy;
	int		result;
	int		player_x;
	int		player_y;

	if (!find_player_coords(map, &player_x, &player_y))
		return (1);
	grid_copy = copy_map_grid(map);
	if (!grid_copy)
		return (return_error("Memory allocation failed for flood fill"));
	result = flood_fill_recursive(grid_copy, player_x, player_y, map);
	free_grid_copy(grid_copy);
	if (!result)
		return (return_error("Map is not properly enclosed by walls"));
	return (1);
}
