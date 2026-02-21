/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:15 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:53:39 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = ms_in_time() + (table->num_philos * 2 * 10);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philosophers[i]->thread, NULL,
				&philosoper, table->philosophers[i]) != 0)
			return (message("%s Couldn't create thread.\n",
					NULL, EXIT_FAILURE));
		i++;
	}
	if (table->num_philos > 1)
	{
		if (pthread_create(&table->grim_counter, NULL,
				&grim_repeat, table) != 0)
			return (message("%s Couldn't create thread.\n",
					NULL, EXIT_FAILURE));
	}
	return (1);
}

int	message(char *str, char *details, int nb)
{
	if (!details)
		printf(str, "philosopher:");
	else
		printf(str, "philosopher:", details);
	return (nb);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("%s\n", "Use: ./philosopher number_of_philosopher");
		return (EXIT_FAILURE);
	}
	if (!is_value_input(argc, argv))
		return (EXIT_FAILURE);
	table = start_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	stop_simulation(table);
	return (EXIT_SUCCESS);
}
