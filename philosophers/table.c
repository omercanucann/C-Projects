/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:39 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:49:33 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	**start_philosophers(t_table *table)
{
	t_philo	**philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo *) * table->num_philos);
	if (!philosophers)
	{
		message("%s malloc error: ", "philosophers", 0);
		return (NULL);
	}
	i = start_philosophers_helper(philosophers, table);
	if (i == 1)
		return (NULL);
	return (philosophers);
}

t_table	*start_table(int argc, char **argv, int i)
{
	t_table	*table;
	int		j;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
	{
		message("%s malloc error: ", "table", 0);
		return (NULL);
	}
	table->num_philos = ft_atoi(argv[i++]);
	table->time_die = ft_atoi(argv[i++]);
	table->time_eat = ft_atoi(argv[i++]);
	table->time_sleep = ft_atoi(argv[i++]);
	table->eat_count = -1;
	if (argc == 6)
		table->eat_count = ft_atoi(argv[i]);
	table->philosophers = start_philosophers(table);
	j = start_table_helper(table);
	if (j == 1)
		return (NULL);
	table->simulator_stop = false;
	return (table);
}
