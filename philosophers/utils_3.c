/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:50 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 16:07:18 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	throw_fork(t_philo *philo)
{
	philo->left_fork = philo->id;
	philo->right_fork = (philo->id + 1) % philo->table->num_philos;
	if (philo->id % 2)
	{
		philo->left_fork = (philo->id + 1) % philo->table->num_philos;
		philo->right_fork = philo->id;
	}
}

int	start_philosophers_helper(t_philo **philosophers, t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_philos)
	{
		philosophers[i] = malloc(sizeof(t_philo) * 1);
		if (!philosophers[i])
		{
			message("%s malloc error: ", "philosophers", 0);
			return (1);
		}
		philosophers[i]->table = table;
		philosophers[i]->id = i;
		philosophers[i]->times_eaten = 0;
		philosophers[i]->is_eating = false;
		philosophers[i]->last_meal = 0;
		if (pthread_mutex_init(&philosophers[i]->meal_time_lock, NULL) != 0)
		{
			message("%s mutex init error: ", "meal_time_lock", 0);
			return (1);
		}
		throw_fork(philosophers[i]);
		i++;
	}
	return (0);
}

static pthread_mutex_t	*start_fork(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!forks)
	{
		message("%s malloc error: ", "forks", 0);
		return (NULL);
	}
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			message("%s mutex init error: ", "forks", 0);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static int	start_mutex(t_table *table)
{
	table->fork_lock = start_fork(table);
	if (!table->fork_lock)
	{
		message("%s mutex init error: ", "forks", 0);
		return (0);
	}
	if (pthread_mutex_init(&table->simulator_stop_lock, 0) != 0)
	{
		message("%s mutex init error: ", "simulator_stop_lock", 0);
		return (0);
	}
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
	{
		message("%s mutex init error: ", "write_lock", 0);
		return (0);
	}
	return (1);
}

int	start_table_helper(t_table *table)
{
	if (!table->philosophers)
	{
		message("%s malloc error: ", "philosophers", 0);
		free(table);
		return (1);
	}
	if (!start_mutex(table))
	{
		message("%s mutex init error: ", "table", 0);
		free(table->philosophers);
		free(table);
		return (1);
	}
	return (0);
}
