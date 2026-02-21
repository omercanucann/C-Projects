/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:40 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 16:33:19 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_process_rotation(t_stack **stack_a, t_stack **stack_b,
	t_stack *tmp, int i)
{
	while (i >= 0)
	{
		if (i == ft_case_rarb(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rarb(stack_a, stack_b, tmp->nbr, 'a');
		else if (i == ft_case_rrarrb(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rrarrb(stack_a, stack_b, tmp->nbr, 'a');
		else if (i == ft_case_rarrb(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rarrb(stack_a, stack_b, tmp->nbr, 'a');
		else if (i == ft_case_rrarb(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rrarb(stack_a, stack_b, tmp->nbr, 'a');
		else
			tmp = tmp->next;
	}
	return (i);
}

t_stack	*ft_sort_b(t_stack **stack_a)
{
	t_stack	*stack_b;

	stack_b = NULL;
	if (ft_lstsize(*stack_a) > 3 && !ft_checksorted(*stack_a))
		ft_pb(stack_a, &stack_b);
	if (ft_lstsize(*stack_a) > 3 && !ft_checksorted(*stack_a))
		ft_sort_b_until_three(stack_a, &stack_b);
	if (!ft_checksorted(*stack_a))
		ft_sort_three(stack_a);
	return (stack_b);
}

t_stack	**ft_sort_a(t_stack **stack_a, t_stack **stack_b)
{
	int		i;
	t_stack	*tmp;

	while (*stack_b)
	{
		tmp = *stack_b;
		i = ft_rotate_ba(*stack_a, *stack_b);
		i = ft_process_rotation_a(stack_a, stack_b, tmp, i);
	}
	return (stack_a);
}

void	ft_sort(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		index;
	int		size;

	stack_b = NULL;
	size = ft_lstsize(*stack_a);
	if (size == 2)
		ft_sa(stack_a);
	else
	{
		stack_b = ft_sort_b(stack_a);
		stack_a = ft_sort_a(stack_a, &stack_b);
		index = ft_find_index(*stack_a, ft_minimum(*stack_a));
		if (index < size - index)
		{
			while ((*stack_a)->nbr != ft_minimum(*stack_a))
				ft_ra(stack_a);
		}
		else
		{
			while ((*stack_a)->nbr != ft_minimum(*stack_a))
				ft_rra(stack_a);
		}
	}
}

void	ft_sort_three(t_stack **stack_a)
{
	int	min_value;
	int	max_value;
	int	first_value;

	min_value = ft_minimum(*stack_a);
	max_value = ft_maximum(*stack_a);
	first_value = (*stack_a)->nbr;
	if (min_value == first_value)
	{
		ft_rra(stack_a);
		ft_sa(stack_a);
	}
	else if (max_value == first_value)
	{
		ft_ra(stack_a);
		if (!ft_checksorted(*stack_a))
			ft_sa(stack_a);
	}
	else
	{
		if (ft_find_index(*stack_a, max_value) == 1)
			ft_rra(stack_a);
		else
			ft_sa(stack_a);
	}
}
