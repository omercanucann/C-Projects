/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:25 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:46:33 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_game(t_game *game)
{
	printf("Cleaning continues... \n");
	free_map(&game->map);
	if (game->mlx.mlx_ptr)
		free_textures(&game->textures, game->mlx.mlx_ptr);
	close_mlx(game);
	printf("Clean is done");
}
