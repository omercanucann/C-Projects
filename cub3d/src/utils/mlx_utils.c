/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:43 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:46:48 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_close(t_game *game)
{
	printf("Window closed, exiting\n");
	clean_game(game);
	exit(0);
}

int	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (return_error("MLX failed to start!"));
	game->mlx.win_width = WIN_WIDTH;
	game->mlx.win_height = WIN_HEIGHT;
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->mlx.win_ptr)
		return (return_error("Could not create window!"));
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->mlx.img_data = mlx_get_data_addr(game->mlx.img_ptr,
			&game->mlx.bits_per_pixel,
			&game->mlx.line_length,
			&game->mlx.endian);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->mlx.win_ptr, 17, 0, handle_close, game);
	printf("MLX started!\n");
	printf("- Window: %dx%d\n", WIN_WIDTH, WIN_HEIGHT);
	printf("- BBP: %d\n", game->mlx.bits_per_pixel);
	printf("- Line Length: %d\n", game->mlx.line_length);
	return (1);
}

void	close_mlx(t_game *game)
{
	if (!game->mlx.mlx_ptr)
		return ;
	if (game->mlx.img_ptr)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
		game->mlx.img_ptr = NULL;
	}
	if (game->mlx.win_ptr)
	{
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
		game->mlx.win_ptr = NULL;
	}
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
		game->mlx.mlx_ptr = NULL;
	}
	printf("MLX Closed.\n");
}
