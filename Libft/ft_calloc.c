/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:26:47 by oucan             #+#    #+#             */
/*   Updated: 2024/10/16 17:02:30 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	pointer = (void *)malloc(count * size);
	if (!pointer)
	{
		return (0);
	}
	ft_bzero(pointer, count * size);
	return (pointer);
}
