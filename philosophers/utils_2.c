/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:48 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:50:52 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_of_sleep_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_lock[philo->left_fork]);
	status_write(philo, 0, FORK_1);
	pthread_mutex_lock(&philo->table->fork_lock[philo->right_fork]);
	status_write(philo, 0, FORK_2);
	status_write(philo, 0, EAT);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = ms_in_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	sleeping_philosophers(philo->table, philo->table->time_eat);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->meal_time_lock);
	status_write(philo, 0, SLEEP);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->left_fork]);
	sleeping_philosophers(philo->table, philo->table->time_sleep);
}

void	set_simulation_flag_of_stop(t_table *table, int state)
{
	pthread_mutex_lock(&table->simulator_stop_lock);
	table->simulator_stop = state;
	pthread_mutex_unlock(&table->simulator_stop_lock);
}

static int	kill_philosoph(t_philo *philo)
{
	time_t	time;

	time = ms_in_time();
	if ((time - philo->last_meal) >= philo->table->time_die)
	{
		set_simulation_flag_of_stop(philo->table, 1);
		status_write(philo, 1, DIE);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (1);
	}
	return (0);
}

static int	reach_condition_end(t_table *table)
{
	unsigned int	i;
	int				all_enough;

	all_enough = 1;
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philosophers[i]->meal_time_lock);
		if (kill_philosoph(table->philosophers[i]))
			return (1);
		if (table->eat_count != -1)
			if (table->philosophers[i]->times_eaten
				< (unsigned int)table->eat_count)
				all_enough = 0;
		pthread_mutex_unlock(&table->philosophers[i]->meal_time_lock);
		i++;
	}
	if (table->eat_count != -1 && all_enough == 1)
	{
		set_simulation_flag_of_stop(table, 1);
		return (1);
	}
	return (0);
}

void	*grim_repeat(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->eat_count == 0)
		return (NULL);
	set_simulation_flag_of_stop(table, 0);
	simulator_start(table->start_time);
	while (1)
	{
		if (reach_condition_end(table) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
