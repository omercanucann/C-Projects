/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:40:54 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:44:33 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	destlength;
	size_t	srclength;
	size_t	i;

	destlength = ft_strlen(dst);
	srclength = ft_strlen(src);
	if (dstsize <= destlength)
	{
		return (dstsize + srclength);
	}
	i = 0;
	while (src[i] != '\0' && (destlength + i) < (dstsize - 1))
	{
		dst[destlength + i] = src[i];
		i++;
	}
	dst[destlength + i] = '\0';
	return (destlength + srclength);
}
