/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:52:01 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 16:08:53 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	int		i;

	i = 0;
	if (argc == 1)
		return (0);
	a = ft_processing(argc, argv);
	if (!a || ft_checkduplicate(a))
	{
		ft_error(a);
	}
	if (!ft_checksorted(a))
		ft_sort(&a);
	ft_free(&a);
	return (0);
}
