/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:28 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 18:55:12 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	list_args(char **argv, t_stack **stack_a)
{
	long	i;

	i = 1;
	while (argv[i] != NULL)
	{
		ft_add_back(stack_a, ft_stack_new(ft_atoitwo(argv[i], *stack_a)));
		i++;
	}
}

int	ft_checkduplicate(t_stack *a)
{
	t_stack	*tmp;

	while (a)
	{
		tmp = a->next;
		while (tmp)
		{
			if (a->nbr == tmp->nbr)
				return (1);
			tmp = tmp->next;
		}
		a = a->next;
	}
	return (0);
}

int	ft_checksorted(t_stack *stack_a)
{
	int	prev;

	if (!stack_a)
		return (1);
	prev = stack_a->nbr;
	stack_a = stack_a->next;
	while (stack_a)
	{
		if (prev > stack_a->nbr)
			return (0);
		prev = stack_a->nbr;
		stack_a = stack_a->next;
	}
	return (1);
}

void	ft_error(t_stack *a)
{
	if (a)
		ft_free(&a);
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	ft_free(t_stack **lst)
{
	t_stack	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		(*lst)->nbr = 0;
		free(*lst);
		*lst = tmp;
	}
}
