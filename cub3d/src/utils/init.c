/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:36 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 18:28:49 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_game_player(t_game *game)
{
	game->player.pos_x = 0.0;
	game->player.pos_y = 0.0;
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.70;
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	game->player.initialized = 0;
}

static void	init_game_map(t_game *game)
{
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.east_texture = NULL;
	game->map.west_texture = NULL;
}

static void	init_game_colors(t_game *game)
{
	game->colors.floor_red = 0;
	game->colors.floor_green = 0;
	game->colors.floor_blue = 0;
	game->colors.ceiling_red = 0;
	game->colors.ceiling_green = 0;
	game->colors.ceiling_blue = 0;
	game->colors.ceiling_color = -1;
	game->colors.floor_color = -1;
}

void	init_game(t_game *game)
{
	init_game_player(game);
	init_game_map(game);
	init_game_colors(game);
}

char	*readline_init(char *readone)
{
	if (!readone)
	{
		readone = malloc(1);
		if (!readone)
			return (NULL);
		readone[0] = '\0';
	}
	return (readone);
}
