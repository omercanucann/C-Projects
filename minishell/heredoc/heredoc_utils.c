/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:29:27 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:29:28 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_data	*global_data(t_data *data)
{
	static t_data	*global_data;

	if (data)
		global_data = data;
	else
		return (global_data);
	return (data);
}

void	set_data(t_data *data)
{
	global_data(data);
}

t_data	*get_data(void)
{
	return (global_data(NULL));
}

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	cleanup_child_process(get_data(), NULL);
	exit(130);
}
