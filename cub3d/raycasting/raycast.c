/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:11:46 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:45:17 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/cub3d.h"

void	ray_pos(t_game *game)
{
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
}

void	ray_cast(t_game *game, int i)
{
	game->ray.camera_x = 2.0 * i / (double)WIN_WIDTH - 1.0;
	game->ray.ray_dir_x = game->player.dir_x
		+ game->player.plane_x * game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir_y
		+ game->player.plane_y * game->ray.camera_x;
}
