/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:21 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:45:02 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# ifndef DEBUG_FORMAT
#  define DEBUG_FORMAT 0
# endif

typedef struct s_philosophers	t_philo;

typedef struct s_table
{
	volatile bool		simulator_stop;
	time_t				start_time;
	time_t				time_die;
	time_t				time_eat;
	time_t				time_sleep;
	unsigned int		num_philos;
	int					eat_count;
	pthread_t			grim_counter;
	pthread_mutex_t		simulator_stop_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*fork_lock;
	t_philo				**philosophers;
}	t_table;

typedef struct s_philosophers
{
	time_t				last_meal;
	unsigned int		id;
	unsigned int		times_eaten;
	unsigned int		left_fork;
	unsigned int		right_fork;
	bool				is_eating;
	pthread_t			thread;
	pthread_mutex_t		meal_time_lock;
	t_table				*table;
}	t_philosophers;

typedef enum e_status
{
	DIE = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	FORK_1 = 4,
	FORK_2 = 5
}	t_status;

typedef struct s_time
{
	int	second;
	int	usecond;
}	t_time;

int		message(char *str, char *details, int nb);
int		ft_atoi(const char *str);
int		is_value_input(int argc, char **argv);
t_table	*start_table(int argc, char **argv, int i);
time_t	ms_in_time(void);
void	simulator_start(time_t start_time);
int		simulation_stop(t_table *table);
void	print_status_debug(t_philo *philo, char *str, t_status status);
void	print_status(t_philo *philo, char *str);
int		has_stop_simulation(t_table *table);
void	sleeping_philosophers(t_table *table, time_t time_sleep);
void	status_write(t_philo *philosoph, int report, t_status status);
void	routine_of_sleep_eat(t_philo *philo);
void	set_simulation_flag_of_stop(t_table *table, int state);
void	*grim_repeat(void *data);
void	*philosoper(void *data);
void	stop_simulation(t_table *table);
int		start_philosophers_helper(t_philo **philosophers, t_table *table);
int		start_table_helper(t_table *table);

#endif