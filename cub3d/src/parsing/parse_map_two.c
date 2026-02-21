/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:06 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 20:14:51 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	count_map_height(char **lines, int start)
{
	int	i;
	int	map_height;

	map_height = 0;
	i = start;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		map_height++;
		i++;
	}
	return (map_height);
}

static char	**build_map_grid(char **lines, int start, int map_height)
{
	char	**map_grid;
	int		i;

	map_grid = malloc(sizeof(char *) * (map_height + 1));
	if (!map_grid)
		return (NULL);
	i = 0;
	while (i < map_height)
	{
		map_grid[i] = ft_strdup(lines[start + i]);
		if (!map_grid[i])
		{
			free_split(map_grid);
			return (NULL);
		}
		i++;
	}
	map_grid[map_height] = NULL;
	return (map_grid);
}

static int	build_map_and_check(char **lines, int start, t_game *game)
{
	int		map_height;
	char	**map_grid;
	int		i;

	map_height = count_map_height(lines, start);
	if (map_height == 0)
		return (return_error("Empty Map"));
	map_grid = build_map_grid(lines, start, map_height);
	if (!map_grid)
		return (return_error("Memory allocation failed"));
	i = start + map_height;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			free_split(map_grid);
			return (return_error("Multiple map sections found"));
		}
		i++;
	}
	game->map.grid = map_grid;
	game->map.height = map_height;
	game->map.width = get_map_width(map_grid);
	return (1);
}

int	parse_map(char **lines, int start, t_game *game)
{
	if (!build_map_and_check(lines, start, game))
		return (0);
	if (!flood_fill_check(&game->map))
		return (0);
	printf("✓ Map is properly enclosed (flood fill passed)\n");
	printf("✓ Map size: %dx%d\n", game->map.width, game->map.height);
	if (!find_player_position(&game->map, &game->player))
		return (0);
	printf("✓ player position: (%.1f, %.1f) Direction: (%.1f, %.1f)\n",
		game->player.pos_x, game->player.pos_y, game->player.dir_x,
		game->player.dir_y);
	return (1);
}

int	handle_player(t_map *map, t_player *player, int x, int y)
{
	if (player->initialized)
		return (return_error("Multiple player starting positions"));
	if (!process_player_at(map, player, x, y))
		return (0);
	return (1);
}
