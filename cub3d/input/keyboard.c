/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:11:18 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:38:54 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/cub3d.h"

void	key_ok_key_right(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	if (keycode == KEY_LEFT)
	{
		game->player.dir_x = game->player.dir_x * cos(-game->player.rot_speed)
			- game->player.dir_y * sin(-game->player.rot_speed);
		game->player.dir_y = old_dir_x * sin(-game->player.rot_speed)
			+ game->player.dir_y * cos(-game->player.rot_speed);
		game->player.plane_x = game->player.plane_x
			* cos(-game->player.rot_speed)
			- game->player.plane_y * sin(-game->player.rot_speed);
		game->player.plane_y = old_plane_x * sin(-game->player.rot_speed)
			+ game->player.plane_y * cos(-game->player.rot_speed);
	}
}

void	key_ok_key_left(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	if (keycode == KEY_RIGHT)
	{
		game->player.dir_x = game->player.dir_x * cos(game->player.rot_speed)
			- game->player.dir_y * sin(game->player.rot_speed);
		game->player.dir_y = old_dir_x * sin(game->player.rot_speed)
			+ game->player.dir_y * cos(game->player.rot_speed);
		game->player.plane_x = game->player.plane_x
			* cos(game->player.rot_speed)
			- game->player.plane_y * sin(game->player.rot_speed);
		game->player.plane_y = old_plane_x * sin(game->player.rot_speed)
			+ game->player.plane_y * cos(game->player.rot_speed);
	}
}

void	key_a_d(int keycode, t_game *game)
{
	double	x;
	double	y;

	key_a_utils(keycode, game);
	if (keycode == KEY_D)
	{
		x = game->player.pos_x + game->player.plane_x * game->player.move_speed;
		y = game->player.pos_y + game->player.plane_y * game->player.move_speed;
		if (game->map.grid[(int)y][(int)x] != '1'
			&& game->map.grid[(int)y][(int)x] != ' '
			&& game->map.grid[(int)y][(int)x] != '\n')
		{
			game->player.pos_x = x;
			game->player.pos_y = y;
		}
	}
}

void	key_w_s(int keycode, t_game *game)
{
	double	x;
	double	y;

	key_w_utils(keycode, game);
	if (keycode == KEY_S)
	{
		x = game->player.pos_x - game->player.dir_x * game->player.move_speed;
		y = game->player.pos_y - game->player.dir_y * game->player.move_speed;
		if (game->map.grid[(int)y][(int)x] != '1'
			&& game->map.grid[(int)y][(int)x] != ' '
			&& game->map.grid[(int)y][(int)x] != '\n')
		{
			game->player.pos_x = x;
			game->player.pos_y = y;
		}
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		printf("Quitting the game\n");
		clean_game(game);
		exit(0);
	}
	key_w_s(keycode, game);
	key_a_d(keycode, game);
	key_ok_key_left(keycode, game);
	key_ok_key_right(keycode, game);
	return (0);
}
