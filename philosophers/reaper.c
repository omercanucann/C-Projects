/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:26 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:48:24 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_stop(t_table *table)
{
	pthread_mutex_lock(&table->simulator_stop_lock);
	if (table->simulator_stop == true)
	{
		pthread_mutex_unlock(&table->simulator_stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->simulator_stop_lock);
	return (1);
}
