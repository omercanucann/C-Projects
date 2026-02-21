/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:22 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:45:29 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/cub3d.h"

void	put_to_image(t_game *game, int x, int y, int color)
{
	int		coordinate;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	coordinate = (y * game->mlx.line_length)
		+ (x * (game->mlx.bits_per_pixel / 8));
	*(unsigned int *)(game->mlx.img_data + coordinate) = color;
}

void	place_pixel(t_game *game, int i)
{
	int	y;
	int	color;

	y = 0;
	while (y < game->ray.draw_start)
	{
		put_to_image(game, i, y, game->colors.ceiling_color);
		y++;
	}
	while (y < game->ray.draw_end)
	{
		color = apply_texture(game, y);
		put_to_image(game, i, y, color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		put_to_image(game, i, y, game->colors.floor_color);
		y++;
	}
}

int	render(void *param)
{
	t_game	*game;
	int		i;

	game = param;
	i = 0;
	while (i < WIN_WIDTH)
	{
		game->ray.hit = 0;
		ray_pos(game);
		ray_cast(game, i);
		calculate_ray_steps(game);
		perform_dda(game);
		draw_wall_column(game);
		wall_size(game);
		wall_draw_height(game);
		place_pixel(game, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}
