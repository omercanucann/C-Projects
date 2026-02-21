/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:27 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:46:36 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_error(char *message)
{
	write(2, "Error\n", 6);
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
}

void	exit_error(char *message, t_game *game)
{
	print_error(message);
	if (game)
		clean_game(game);
	exit(1);
}

int	return_error(char *message)
{
	print_error(message);
	return (0);
}
