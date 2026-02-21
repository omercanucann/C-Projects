/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:06 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:45:25 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/cub3d.h"

int	get_wall_dir(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			return (1);
		else
			return (2);
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
			return (3);
		else
			return (4);
	}
}

void	wall_draw_height(t_game *game)
{
	if (game->ray.line_height <= 0)
		return ;
	game->ray.draw_start = WIN_HEIGHT / 2 - (game->ray.line_height / 2);
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.draw_start + game->ray.line_height;
	if (game->ray.draw_end >= WIN_HEIGHT)
		game->ray.draw_end = WIN_HEIGHT - 1;
}

void	wall_size(t_game *game)
{
	game->ray.line_height = (int)(WIN_HEIGHT / game->ray.wall_dist);
}

void	draw_wall_column(t_game *game)
{
	if (game->ray.side == 0)
	{
		game->ray.wall_dist = (game->ray.map_x - game->player.pos_x
				+ (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x ;
	}
	else if (game->ray.side == 1)
	{
		game->ray.wall_dist = (game->ray.map_y - game->player.pos_y
				+ (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y ;
	}
}
