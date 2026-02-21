/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:53 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:51:42 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (-1);
		str++;
	}
	if (sign == -1 || result > INT_MAX)
		return (-1);
	return ((int)result);
}

void	print_status_debug(t_philo *philo, char *str, t_status status)
{
	if (status == FORK_1)
		printf("[%10ld]\t%03u\t%s\e[0m: fork [%u]\n",
			ms_in_time() - philo->table->start_time,
			philo->id + 1,
			str,
			philo->left_fork);
	else if (status == FORK_2)
		printf("[%10ld]\t%03u\t%s\e[0m: fork [%u]\n",
			ms_in_time() - philo->table->start_time,
			philo->id + 1,
			str,
			philo->right_fork);
	else
		printf("[%10ld]\t%03u\t%s\e[0m\n",
			ms_in_time() - philo->table->start_time,
			philo->id + 1,
			str);
}

void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n",
		ms_in_time() - philo->table->start_time, philo->id + 1, str);
}

int	has_stop_simulation(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->simulator_stop_lock);
	if (table->simulator_stop == 1)
		i = 1;
	pthread_mutex_unlock(&table->simulator_stop_lock);
	return (i);
}
