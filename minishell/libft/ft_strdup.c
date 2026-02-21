/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:17:23 by oucan             #+#    #+#             */
/*   Updated: 2024/10/27 16:23:35 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1) + 1;
	new = (char *)malloc(sizeof(*new) * len);
	if (!new)
		return (NULL);
	return ((char *)ft_memcpy(new, s1, len));
}
