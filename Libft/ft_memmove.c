/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:31:25 by oucan             #+#    #+#             */
/*   Updated: 2024/10/27 17:42:18 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!src && !dst)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d < s)
	{
		while (len--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		s += len;
		d += len;
		while (len--)
		{
			*(--d) = *(--s);
		}
	}
	return (dst);
}
