/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:56:55 by oucan             #+#    #+#             */
/*   Updated: 2025/01/17 16:27:02 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	args_check(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Wrong parameter count");
		exit(EXIT_FAILURE);
	}
	while (argv[1][i])
	{
		if (!ft_strchr("0123456789", argv[1][i]))
		{
			ft_printf("Wrong PID!");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (*argv[2] == 0)
	{
		ft_printf("Empty message");
		exit(EXIT_FAILURE);
	}
}

void	send_message(int server_procces_id, char *message)
{
	int	bit;

	while (*message)
	{
		bit = 8;
		while (bit--)
		{
			if (*message & 0b10000000)
				kill(server_procces_id, SIGUSR1);
			else
				kill(server_procces_id, SIGUSR2);
			usleep(3000);
			*message <<= 1;
		}
		message++;
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("Signal is sending\n");
}

void	config_signals(void)
{
	struct sigaction	newsigaction;

	newsigaction.sa_handler = &signal_handler;
	newsigaction.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &newsigaction, NULL) == -1)
		ft_printf("Failed to change SIGUSR1's action");
	if (sigaction(SIGUSR2, &newsigaction, NULL) == -1)
		ft_printf("Failed to change SIGUSR2's action");
}

int	main(int argc, char **argv)
{
	ft_printf("CLIENT PID = %d\n\n", getpid());
	args_check(argc, argv);
	config_signals();
	send_message(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
