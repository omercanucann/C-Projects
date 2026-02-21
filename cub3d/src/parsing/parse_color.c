/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:52 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 19:17:22 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int	parse_rgb_values(char *str, int *r, int *g, int *b)
{
	char	**parts;
	int		ret;

	if (!str)
		return (0);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_split(parts);
		return (0);
	}
	ret = parse_components(parts, r, g, b);
	free_split(parts);
	return (ret);
}

static int	get_trimmed_values(char *line, char **trimed, char **values)
{
	*trimed = ft_strtrim_whitespace(line);
	if (!*trimed)
		return (0);
	if (ft_strncmp(*trimed, "F ", 2) == 0)
		*values = ft_strtrim_whitespace(*trimed + 2);
	else if (ft_strncmp(*trimed, "C ", 2) == 0)
		*values = ft_strtrim_whitespace(*trimed + 2);
	else
	{
		free(*trimed);
		return (0);
	}
	if (!*values)
	{
		free(*trimed);
		return (0);
	}
	return (1);
}

static int	fill_output_colors(t_color_parse_result *out,
	char *trimed, char *values)
{
	if (!parse_rgb_values(values, &out->red, &out->green, &out->blue))
	{
		free(trimed);
		free(values);
		return (0);
	}
	out->trimed = trimed;
	out->values = values;
	return (1);
}

int	get_color_values_from_line(char *line, t_color_parse_result *out)
{
	char	*trimed;
	char	*values;

	trimed = NULL;
	values = NULL;
	if (!get_trimmed_values(line, &trimed, &values))
		return (0);
	if (!fill_output_colors(out, trimed, values))
		return (0);
	return (1);
}
