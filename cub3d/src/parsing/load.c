/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:38 by oucan             #+#    #+#             */
/*   Updated: 2025/12/03 19:10:02 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	load_textures(t_game *game)
{
	printf("Textures are loading...\n");
	if (!game->map.north_texture || !game->map.south_texture
		|| !game->map.east_texture || !game->map.west_texture)
		return (return_error("All tissues must be (NO, SO, EA, WE)"));
	if (!load_single_texture(game, &game->textures.north,
			game->map.north_texture))
		return (return_error("North texture could not be loaded"));
	printf("North texture: %s (%dx%d)\n", game->map.north_texture,
		game->textures.north.width, game->textures.north.height);
	if (!load_single_texture(game, &game->textures.south,
			game->map.south_texture))
		return (return_error("South texture could not be loaded"));
	printf("South texture: %s (%dx%d)\n", game->map.south_texture,
		game->textures.south.width, game->textures.south.height);
	if (!load_single_texture(game, &game->textures.east,
			game->map.east_texture))
		return (return_error("East texture could not be loaded"));
	printf("East texture: %s (%dx%d)\n", game->map.east_texture,
		game->textures.east.width, game->textures.east.height);
	if (!load_single_texture(game, &game->textures.west,
			game->map.west_texture))
		return (return_error("West texture could not be loaded"));
	printf("West texture: %s (%dx%d)\n", game->map.west_texture,
		game->textures.west.width, game->textures.west.height);
	return (1);
}

void	flood_component(t_map *map, int y, int x, t_flood *f)
{
	int	index;

	if (y < 0 || x < 0 || y >= f->height || x >= f->width)
		return ;
	if (get_char(map, y, x) == ' ')
		return ;
	index = y * f->width + x;
	if (f->visited[index])
		return ;
	f->visited[index] = 1;
	flood_component(map, y + 1, x, f);
	flood_component(map, y - 1, x, f);
	flood_component(map, y, x + 1, f);
	flood_component(map, y, x - 1, f);
}

void	flood_outside(t_map *map, int y, int x, t_flood *f)
{
	t_bounds	b;
	int			index;
	int			w;

	b.height = f->height;
	b.width = f->width;
	w = f->width + 2;
	if (y < 0 || x < 0 || y >= b.height + 2 || x >= b.width + 2)
		return ;
	index = y * w + x;
	if (f->visited[index])
		return ;
	if (get_ext_char(map, y, x, &b) == '1')
		return ;
	f->visited[index] = 1;
	flood_outside(map, y + 1, x, f);
	flood_outside(map, y - 1, x, f);
	flood_outside(map, y, x + 1, f);
	flood_outside(map, y, x - 1, f);
}

int	count_loop(t_map *map, t_flood *f, int height, int width)
{
	int	y;
	int	x;
	int	c;

	c = 0;
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			c += process_component(map, f, y, x);
	}
	return (c);
}

int	process_component(t_map *map, t_flood *f, int y, int x)
{
	if (get_char(map, y, x) != ' ' && !f->visited[y * f->width + x])
	{
		flood_component(map, y, x, f);
		return (1);
	}
	return (0);
}
