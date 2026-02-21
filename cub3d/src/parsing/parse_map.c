/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:13 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:46:15 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_player_direction_vector(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

static void	set_player_plane_vector(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->plane_x = 0.70;
		player->plane_y = 0.0;
	}
	else if (direction == 'S')
	{
		player->plane_x = -0.70;
		player->plane_y = 0;
	}
	else if (direction == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.70;
	}
	else if (direction == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.70;
	}
}

void	init_player_direction(t_player *player, char direction)
{
	set_player_direction_vector(player, direction);
	set_player_plane_vector(player, direction);
}

int	process_player_at(t_map *map, t_player *player, int x, int y)
{
	char	direction;

	direction = map->grid[y][x];
	player->pos_x = x + 0.5;
	player->pos_y = y + 0.5;
	map->grid[y][x] = '0';
	init_player_direction(player, direction);
	player->initialized = 1;
	return (1);
}

int	find_player_position(t_map *map, t_player *player)
{
	if (!map || !player)
		return (return_error("Invalid arguments"));
	if (!search_player_in_map(map, player))
		return (return_error("Player starting position not found"));
	return (1);
}
