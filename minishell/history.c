/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:35:11 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 20:35:12 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*save_history(t_data data)
{
	data.input = readline("minishell> ");
	if (!data.input)
	{
		printf("exit\n");
		if (data.env)
			free_env(data.env);
		return (NULL);
	}
	if (data.input)
		add_history(data.input);
	return (data.input);
}
