/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:42 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:50:10 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ms_in_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	simulator_start(time_t start_time)
{
	while (ms_in_time() < start_time)
		continue ;
}

void	sleeping_philosophers(t_table *table, time_t time_sleep)
{
	time_t	wake;

	wake = ms_in_time() + time_sleep;
	while (ms_in_time() < wake)
	{
		if (has_stop_simulation(table))
			break ;
		usleep(100);
	}
}
