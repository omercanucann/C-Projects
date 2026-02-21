/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:48:52 by oucan             #+#    #+#             */
/*   Updated: 2025/01/13 20:11:37 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handle_signaluser(int signalnum, siginfo_t *info, void *ucontent)
{
	static int				bit = -1;
	static unsigned char	character;

	(void)ucontent;
	if (bit < 0)
		bit = 7;
	if (signalnum == SIGUSR1)
		character |= (1 << bit);
	bit--;
	if (bit < 0)
	{
		write(STDOUT_FILENO, &character, 1);
		character = 0;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_printf("Server failed to send SIGUSR1");
	}
}

void	config_signals(void)
{
	struct sigaction	newsigaction;

	newsigaction.sa_sigaction = &handle_signaluser;
	newsigaction.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &newsigaction, NULL) == -1)
		ft_printf("Failed to change SIGUSR1's action");
	if (sigaction(SIGUSR2, &newsigaction, NULL) == -1)
		ft_printf("Failed to change SIGUSR2's action");
}

int	main(void)
{
	ft_printf("SERVER PID = %d\n\n", getpid());
	config_signals();
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
