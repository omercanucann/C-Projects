/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:31:39 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:38:47 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/cub3d.h"

void	key_a_utils(int keycode, t_game *game)
{
	double	x;
	double	y;

	if (keycode == KEY_A)
	{
		x = game->player.pos_x - game->player.plane_x * game->player.move_speed;
		y = game->player.pos_y - game->player.plane_y * game->player.move_speed;
		if (game->map.grid[(int)y][(int)x] != '1'
			&& game->map.grid[(int)y][(int)x] != ' '
			&& game->map.grid[(int)y][(int)x] != '\n')
		{
			game->player.pos_x = x;
			game->player.pos_y = y;
		}
	}
}

void	key_w_utils(int keycode, t_game *game)
{
	double	x;
	double	y;

	if (keycode == KEY_W)
	{
		x = game->player.pos_x + game->player.dir_x * game->player.move_speed;
		y = game->player.pos_y + game->player.dir_y * game->player.move_speed;
		if (game->map.grid[(int)y][(int)x] != '1'
			&& game->map.grid[(int)y][(int)x] != ' '
			&& game->map.grid[(int)y][(int)x] != '\n')
		{
			game->player.pos_x = x;
			game->player.pos_y = y;
		}
	}
}
