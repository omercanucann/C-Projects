/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:11:48 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:45:19 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/include/cub3d.h"

t_texture	*get_texture_by_dir(t_game *game, int dir)
{
	if (dir == 1)
		return (&game->textures.east);
	else if (dir == 2)
		return (&game->textures.west);
	else if (dir == 3)
		return (&game->textures.south);
	else
		return (&game->textures.north);
}

int	calculate_texture_y(t_game *game, int y, t_texture *tex)
{
	int		texture_y;

	texture_y = ((y - (WIN_HEIGHT - game->ray.line_height) / 2)
			* tex->height) / game->ray.line_height;
	if (texture_y < 0)
		texture_y = 0;
	if (texture_y >= tex->height)
		texture_y = tex->height - 1;
	return (texture_y);
}

int	calculate_texture_x(t_game *game, t_texture *tex)
{
	int	texture_x;

	texture_x = (int)(game->ray.wall_surface_x * (double)tex->width);
	if ((game->ray.side == 0 && game->ray.ray_dir_x < 0)
		|| (game->ray.side == 1 && game->ray.ray_dir_y > 0))
		texture_x = tex->width - texture_x - 1;
	return (texture_x);
}

int	get_texture_color(t_texture *tex, int texture_x, int texture_y)
{
	int	pixel_index;
	int	color;

	if (texture_x < 0 || texture_x >= tex->width
		|| texture_y < 0 || texture_y >= tex->height)
		return (0);
	pixel_index = (texture_y * tex->line_len) + (texture_x * (tex->bpp / 8));
	color = *(int *)(tex->data + pixel_index);
	return (color);
}

int	apply_texture(t_game *game, int y)
{
	t_texture	*tex;
	int			texture_x;
	int			texture_y;
	int			dir;

	dir = get_wall_dir(game);
	if (dir == 1 || dir == 2)
	{
		game->ray.wall_surface_x = game->player.pos_y
			+ (game->ray.wall_dist * game->ray.ray_dir_y);
	}
	else
	{
		game->ray.wall_surface_x = game->player.pos_x
			+ (game->ray.wall_dist * game->ray.ray_dir_x);
	}
	game->ray.wall_surface_x -= (int)game->ray.wall_surface_x;
	tex = get_texture_by_dir(game, dir);
	texture_x = calculate_texture_x(game, tex);
	texture_y = calculate_texture_y(game, y, tex);
	return (get_texture_color(tex, texture_x, texture_y));
}
