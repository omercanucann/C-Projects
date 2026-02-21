/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:59 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 20:26:56 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	if (line[i] == '0' || line[i] == '1' || line[i] == ' ')
		return (1);
	return (0);
}

static char	**append_line(char **lines, char *line, int count)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (count + 2));
	if (!temp)
	{
		free(line);
		free_split(lines);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		temp[i] = lines[i];
		i++;
	}
	if (lines)
		free(lines);
	temp[count] = line;
	temp[count + 1] = NULL;
	return (temp);
}

char	**read_file_lines(int fd)
{
	char	*line;
	char	**lines;
	int		count;

	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines = append_line(lines, line, count);
		if (!lines)
			return (NULL);
		count++;
		line = get_next_line(fd);
	}
	return (lines);
}
