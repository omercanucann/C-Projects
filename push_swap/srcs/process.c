/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:58 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 18:46:20 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoitwo(const char *str, t_stack *a)
{
	long		sign;
	long long	res;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			ft_error(a);
		res = res * 10 + (*str - '0');
		if (res > 2147483647 || (res * sign) < -2147483648)
			ft_error(a);
		str++;
	}
	return ((int)(res * sign));
}

int	ft_atoithree(const char *str, t_stack *a, char **temp)
{
	long		sign;
	long long	res;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*(str + 1) == '\0' || !(*(str + 1) >= '0' && *(str + 1) <= '9'))
			ft_errortwo(a, temp);
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			ft_errortwo(a, temp);
		res = res * 10 + (*str - '0');
		if (res > 2147483647 || (res * sign) < -2147483648)
			ft_errortwo(a, temp);
		str++;
	}
	return ((int)(res * sign));
}

static void	fill_stack(t_stack **a, char **temp)
{
	int	i;
	int	num;

	i = 0;
	while (temp[i])
	{
		num = ft_atoithree(temp[i], *a, temp);
		ft_add_back(a, ft_stack_new(num));
		i++;
	}
}

t_stack	*ft_sub_processing(char **argv)
{
	t_stack	*a;
	char	**temp;

	a = NULL;
	temp = ft_split(argv[1], ' ');
	if (!temp)
		return (NULL);
	fill_stack(&a, temp);
	ft_freestr(temp);
	return (a);
}

t_stack	*ft_processing(int argc, char **argv)
{
	t_stack	*a;
	int		i;
	int		j;

	i = 1;
	a = NULL;
	if (argc < 2)
		ft_error(a);
	if (argc == 2)
		a = ft_sub_processing(argv);
	else
	{
		while (i < argc)
		{
			j = ft_atoitwo(argv[i], a);
			ft_add_back(&a, ft_stack_new(j));
			i++;
		}
	}
	return (a);
}
