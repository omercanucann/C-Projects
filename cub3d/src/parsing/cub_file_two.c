/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:31 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:45:43 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_elements_and_map(char **lines, t_game *game)
{
	int	map_start;

	if (!parse_elements(lines, game, &map_start))
	{
		free_split(lines);
		return (0);
	}
	if (!parse_map_and_validate(lines, map_start, game))
	{
		free_split(lines);
		return (0);
	}
	free_split(lines);
	return (1);
}

int	parse_cub_file(char *file, t_game *game)
{
	char	**lines;

	lines = read_and_validate_file(file);
	if (!lines)
		return (0);
	if (!parse_elements_and_map(lines, game))
		return (0);
	if (!load_textures(game))
		return (0);
	return (1);
}
