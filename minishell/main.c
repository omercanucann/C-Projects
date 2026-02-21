/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:35:16 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 20:35:17 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.exit_status = 0;
	if (argc == 1)
		interactive(&data, env);
	(void)argv;
	(void)argc;
	return (data.exit_status);
}
