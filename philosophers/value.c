/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:37:55 by oucan             #+#    #+#             */
/*   Updated: 2025/07/27 15:52:41 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	contain_only_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	number_checker(int i, int number, char *arg)
{
	if (i != 1 && number == -1)
		return (message("%s invalid input: %s", arg, 0));
	return (1);
}

int	is_value_input(int argc, char **argv)
{
	int	i;
	int	num;
	int	control;

	i = 1;
	while (i < argc)
	{
		if (!contain_only_num(argv[i]))
			return (message("%s invalid input: %s\n", argv[i], 0));
		num = ft_atoi(argv[i]);
		control = number_checker(i, num, argv[i]);
		if (control == 0)
			return (0);
		i++;
	}
	return (1);
}
