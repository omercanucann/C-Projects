/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:39:39 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 19:23:38 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_all_digits(char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_single_component(char *part, int *out)
{
	char	*trimmed;

	if (!part)
		return (0);
	trimmed = ft_strtrim_whitespace(part);
	if (!trimmed)
		return (0);
	if (!is_all_digits(trimmed))
	{
		free(trimmed);
		return (0);
	}
	*out = ft_atoi(trimmed);
	free(trimmed);
	return (1);
}

int	parse_components(char **parts, int *r, int *g, int *b)
{
	int	vals[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!parse_single_component(parts[i], &vals[i]))
			return (0);
		i++;
	}
	if (vals[0] < 0 || vals[0] > 255 || vals[1] < 0 || vals[1] > 255
		|| vals[2] < 0 || vals[2] > 255)
		return (0);
	*r = vals[0];
	*g = vals[1];
	*b = vals[2];
	return (1);
}
