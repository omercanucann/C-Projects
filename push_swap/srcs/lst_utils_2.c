/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:52 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 16:38:07 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_find_index(t_stack *a, int nbr)
{
	int	i;

	i = 0;
	while (a->nbr != nbr)
	{
		i++;
		a = a->next;
	}
	return (i);
}

int	ft_find_place_b(t_stack *stack_b, int nbr_push)
{
	int		i;
	t_stack	*tmp;

	i = 1;
	if (nbr_push > stack_b->nbr && nbr_push < ft_lstlast(stack_b)->nbr)
		return (0);
	else if (nbr_push > ft_maximum(stack_b) || nbr_push < ft_minimum(stack_b))
		return (ft_find_index(stack_b, ft_maximum(stack_b)));
	tmp = stack_b->next;
	while (stack_b->nbr < nbr_push || tmp->nbr > nbr_push)
	{
		stack_b = stack_b->next;
		tmp = stack_b->next;
		i++;
	}
	return (i);
}

int	ft_find_place_a(t_stack *stack_a, int nbr_push)
{
	int		i;
	t_stack	*tmp;

	i = 1;
	if (nbr_push < stack_a->nbr && nbr_push > ft_lstlast(stack_a)->nbr)
		return (0);
	else if (nbr_push > ft_maximum(stack_a) || nbr_push < ft_minimum(stack_a))
		return (ft_find_index(stack_a, ft_minimum(stack_a)));
	tmp = stack_a->next;
	while (stack_a->nbr > nbr_push || tmp->nbr < nbr_push)
	{
		stack_a = stack_a->next;
		tmp = stack_a->next;
		i++;
	}
	return (i);
}

t_stack	*ft_stack_new(int content)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		ft_error(new);
	new->nbr = content;
	new->next = NULL;
	return (new);
}
