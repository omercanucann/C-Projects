/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:39 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:46:45 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	if (map->grid)
		free_split(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->east_texture = NULL;
	map->west_texture = NULL;
}

void	free_textures(t_textures *textures, void *mlx_ptr)
{
	if (!textures || !mlx_ptr)
		return ;
	if (textures->north.img)
		mlx_destroy_image(mlx_ptr, textures->north.img);
	if (textures->south.img)
		mlx_destroy_image(mlx_ptr, textures->south.img);
	if (textures->east.img)
		mlx_destroy_image(mlx_ptr, textures->east.img);
	if (textures->west.img)
		mlx_destroy_image(mlx_ptr, textures->west.img);
	ft_memset(textures, 0, sizeof(t_textures));
}
