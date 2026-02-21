/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:33 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 20:26:52 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**read_and_validate_file(char *file)
{
	int		fd;
	char	**lines;

	if (!check_file_extension(file))
	{
		return_error("Invalid file extension. (should be .cub)");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		return_error("File cannot open!");
		return (NULL);
	}
	lines = read_file_lines(fd);
	close(fd);
	if (!lines)
	{
		return_error("File cannot read!");
		return (NULL);
	}
	return (lines);
}

static int	process_line(char *line, t_game *game, int *elements_found)
{
	if (parse_texture_line(line, &game->map))
	{
		(*elements_found)++;
		return (1);
	}
	else if (parse_color_line(line, &game->colors))
	{
		(*elements_found)++;
		return (1);
	}
	printf("DEBUG: Problem line: '%s'\n", line);
	return (return_error("Invalid elements line"));
}

static int	find_map_start(int elements_found, int i, int *map_start)
{
	if (elements_found < 6)
	{
		printf("ERROR: Map started but only %d/6 elements found!\n",
			elements_found);
		return (return_error("Missing texture or color elements"));
	}
	*map_start = i;
	return (1);
}

int	parse_elements(char **lines, t_game *game, int *map_start)
{
	int	i;
	int	elements_found;

	i = 0;
	elements_found = 0;
	*map_start = -1;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
			;
		else if (is_map_line(lines[i]))
			return (find_map_start(elements_found, i, map_start));
		else if (!process_line(lines[i], game, &elements_found))
			return (0);
		i++;
	}
	if (*map_start == -1)
		return (return_error("No map found in file"));
	return (1);
}

int	parse_map_and_validate(char **lines, int map_start, t_game *game)
{
	if (map_start == -1 || !parse_map(lines, map_start, game))
		return (return_error("Error Map Parsing!"));
	return (1);
}
