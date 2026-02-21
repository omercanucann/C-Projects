/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:25 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 15:55:34 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_add_back(t_stack **stack, t_stack *stack_new)
{
	if (!stack)
		return ;
	if (!*stack)
		*stack = stack_new;
	else
		(ft_lstlast(*stack))->next = stack_new;
}

void	ft_sort_b_until_three(t_stack **stack_a, t_stack **stack_b)
{
	int		i;
	t_stack	*tmp;

	while (ft_lstsize(*stack_a) > 3 && !ft_checksorted(*stack_a))
	{
		tmp = *stack_a;
		i = ft_rotate_ab(*stack_a, *stack_b);
		i = ft_process_rotation(stack_a, stack_b, tmp, i);
	}
}
