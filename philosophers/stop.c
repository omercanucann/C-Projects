/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:32 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:48:59 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->fork_lock)
		free(table->fork_lock);
	if (table->philosophers != NULL)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->philosophers[i] != NULL)
				free(table->philosophers[i]);
			i++;
		}
		free(table->philosophers);
	}
	free(table);
	return (NULL);
}

void	mutex_destroy(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->fork_lock[i]);
		pthread_mutex_destroy(&table->philosophers[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->simulator_stop_lock);
}

void	out_write(t_table *table)
{
	unsigned int	i;
	unsigned int	count;

	count = 0;
	i = 0;
	while (i < table->num_philos)
	{
		if (table->philosophers[i]->times_eaten
			>= (unsigned int)table->eat_count)
			count++;
		i++;
	}
	pthread_mutex_lock(&table->write_lock);
	printf("%d%d philosophers had at least %d meals. \n",
		count, table->num_philos, table->eat_count);
	pthread_mutex_unlock(&table->write_lock);
}

void	stop_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (table->num_philos > 1)
		pthread_join(table->grim_counter, NULL);
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i]->thread, NULL);
		i++;
	}
	if (DEBUG_FORMAT == 1 && table->eat_count != -1)
		out_write(table);
	mutex_destroy(table);
	free_table(table);
}
