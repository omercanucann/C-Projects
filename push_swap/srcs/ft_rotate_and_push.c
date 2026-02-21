/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_and_push.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:33 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 16:33:02 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_put_rarb(t_stack **a, t_stack **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->nbr != c && ft_find_place_b(*b, c) > 0)
			ft_rr(a, b);
		while ((*a)->nbr != c)
			ft_ra(a);
		while (ft_find_place_b(*b, c) > 0)
			ft_rb(b);
		ft_pb(a, b);
	}
	else
	{
		while ((*b)->nbr != c && ft_find_place_a(*a, c) > 0)
			ft_rr(a, b);
		while ((*b)->nbr != c)
			ft_rb(b);
		while (ft_find_place_a(*a, c) > 0)
			ft_ra(a);
		ft_pa(a, b);
	}
	return (-1);
}

int	ft_put_rrarrb(t_stack **a, t_stack **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->nbr != c && ft_find_place_b(*b, c) > 0)
			ft_rrr(a, b);
		while ((*a)->nbr != c)
			ft_rra(a);
		while (ft_find_place_b(*b, c) > 0)
			ft_rrb(b);
		ft_pb(a, b);
	}
	else
	{
		while ((*b)->nbr != c && ft_find_place_a(*a, c) > 0)
			ft_rrr(a, b);
		while ((*b)->nbr != c)
			ft_rrb(b);
		while (ft_find_place_a(*a, c) > 0)
			ft_rra(a);
		ft_pa(a, b);
	}
	return (-1);
}

int	ft_put_rrarb(t_stack **a, t_stack **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->nbr != c)
			ft_rra(a);
		while (ft_find_place_b(*b, c) > 0)
			ft_rb(b);
		ft_pb(a, b);
	}
	else
	{
		while (ft_find_place_a(*a, c) > 0)
			ft_rra(a);
		while ((*b)->nbr != c)
			ft_rb(b);
		ft_pa(a, b);
	}
	return (-1);
}

int	ft_put_rarrb(t_stack **a, t_stack **b, int c, char s)
{
	if (s == 'a')
	{
		while ((*a)->nbr != c)
			ft_ra(a);
		while (ft_find_place_b(*b, c) > 0)
			ft_rrb(b);
		ft_pb(a, b);
	}
	else
	{
		while (ft_find_place_a(*a, c) > 0)
			ft_ra(a);
		while ((*b)->nbr != c)
			ft_rrb(b);
		ft_pa(a, b);
	}
	return (-1);
}

int	ft_process_rotation_a(t_stack **stack_a, t_stack **stack_b,
	t_stack *tmp, int i)
{
	while (i >= 0)
	{
		if (i == ft_case_rarb_a(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rarb(stack_a, stack_b, tmp->nbr, 'b');
		else if (i == ft_case_rarrb_a(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rarrb(stack_a, stack_b, tmp->nbr, 'b');
		else if (i == ft_case_rrarrb_a(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rrarrb(stack_a, stack_b, tmp->nbr, 'b');
		else if (i == ft_case_rrarb_a(*stack_a, *stack_b, tmp->nbr))
			i = ft_put_rrarb(stack_a, stack_b, tmp->nbr, 'b');
		else
			tmp = tmp->next;
	}
	return (i);
}
