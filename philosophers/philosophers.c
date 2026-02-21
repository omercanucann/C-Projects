/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:24 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:47:44 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_debug_status(t_philo *philo, t_status status)
{
	if (status == DIE)
		print_status_debug(philo, "died", status);
	else if (status == EAT)
		print_status_debug(philo, "is eating", status);
	else if (status == SLEEP)
		print_status_debug(philo, "is sleeping", status);
	else if (status == THINK)
		print_status_debug(philo, "is thinking", status);
	else if (status == FORK_1)
		print_status_debug(philo, "has taken a fork", status);
	else if (status == FORK_2)
		print_status_debug(philo, "has taken a fork", status);
}

static void	routine_of_think(t_philo *philo, int slient)
{
	time_t	think_time;

	pthread_mutex_lock(&philo->meal_time_lock);
	think_time = (philo->table->time_die
			- (ms_in_time() - philo->last_meal)
			- philo->table->time_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (think_time < 0)
		think_time = 0;
	if (think_time == 0 && slient == 1)
		think_time = 1;
	if (think_time > 600)
		think_time = 200;
	if (slient == 0)
		status_write(philo, 0, THINK);
	sleeping_philosophers(philo->table, think_time);
}

void	status_write(t_philo *philo, int reaperter, t_status status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (has_stop_simulation(philo->table) == 1 && reaperter == 0)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (DEBUG_FORMAT == 1)
	{
		write_debug_status(philo, status);
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (status == DIE)
		print_status(philo, "died");
	else if (status == EAT)
		print_status(philo, "is eating");
	else if (status == SLEEP)
		print_status(philo, "is sleeping");
	else if (status == THINK)
		print_status(philo, "is thinking");
	else if (status == FORK_1 || status == FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);
}

static void	*alone_philosoph_routine(t_philo *philosoph)
{
	pthread_mutex_lock(&philosoph->table->fork_lock[philosoph->left_fork]);
	status_write(philosoph, 0, FORK_1);
	sleeping_philosophers(philosoph->table, philosoph->table->time_die);
	status_write(philosoph, 0, DIE);
	pthread_mutex_unlock(&philosoph->table->fork_lock[philosoph->left_fork]);
	return (NULL);
}

void	*philosoper(void *data)
{
	t_philo	*philosoph;

	philosoph = (t_philo *)data;
	if (philosoph->table->eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philosoph->meal_time_lock);
	philosoph->last_meal = philosoph->table->start_time;
	pthread_mutex_unlock(&philosoph->meal_time_lock);
	simulator_start(philosoph->table->start_time);
	if (philosoph->table->time_die == 0)
		return (NULL);
	if (philosoph->table->num_philos == 1)
		return (alone_philosoph_routine(philosoph));
	else if (philosoph->id % 2)
		routine_of_think(philosoph, 1);
	while (has_stop_simulation(philosoph->table) == 0)
	{
		routine_of_sleep_eat(philosoph);
		routine_of_think(philosoph, 0);
	}
	return (NULL);
}
