/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:23 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:24 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*save_separator(t_token **token_list, char *str, int type)
{
	int		i;
	char	*spr;
	char	*start_spr;

	if (type == APPEND || type == HEREDOC)
	{
		spr = malloc(sizeof(char) * 3);
		i = 3;
	}
	else if (type == PIPE || type == INPUT || type == TRUNC)
	{
		spr = malloc(sizeof(char) * 2);
		i = 2;
	}
	else
		return (str);
	start_spr = spr;
	while (--i > 0)
	{
		*spr = *str;
		spr++;
		str++;
	}
	*spr = '\0';
	return (create_token(token_list, start_spr, type, 0), free(start_spr), str);
}
