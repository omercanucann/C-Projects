/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:12:50 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 19:17:03 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	handle_floor_color(t_color_parse_result *res, t_colors *colors)
{
	if (colors->floor_color != -1)
		return (return_error("Duplicate floor color"));
	colors->floor_red = res->red;
	colors->floor_green = res->green;
	colors->floor_blue = res->blue;
	colors->floor_color = create_color(res->red, res->green, res->blue);
	printf("Floor color: RGB(%d, %d, %d)\n", res->red, res->green, res->blue);
	return (1);
}

static int	handle_ceiling_color(t_color_parse_result *res, t_colors *colors)
{
	if (colors->ceiling_color != -1)
		return (return_error("Duplicate ceiling color"));
	colors->ceiling_red = res->red;
	colors->ceiling_green = res->green;
	colors->ceiling_blue = res->blue;
	colors->ceiling_color = create_color(res->red, res->green, res->blue);
	printf("Ceiling color: RGB(%d, %d, %d)\n",
		res->red, res->green, res->blue);
	return (1);
}

int	parse_color_line(char *line, t_colors *colors)
{
	t_color_parse_result	res;

	if (!get_color_values_from_line(line, &res))
		return (0);
	if (ft_strncmp(res.trimed, "F ", 2) == 0)
	{
		if (!handle_floor_color(&res, colors))
		{
			free(res.trimed);
			free(res.values);
			return (0);
		}
	}
	else if (ft_strncmp(res.trimed, "C ", 2) == 0)
	{
		if (!handle_ceiling_color(&res, colors))
		{
			free(res.trimed);
			free(res.values);
			return (0);
		}
	}
	free(res.trimed);
	free(res.values);
	return (1);
}
