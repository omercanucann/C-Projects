/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:03:00 by oucan             #+#    #+#             */
/*   Updated: 2025/07/18 20:27:09 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	signal_handler(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	execution_signal_handler(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
	}
}

void	simple_signal_handler(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
	}
}

int	check_signal(void)
{
	int	sig;

	sig = g_signal_received;
	g_signal_received = 0;
	return (sig);
}
