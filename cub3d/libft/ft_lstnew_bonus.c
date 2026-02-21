/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:52:20 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 15:43:40 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nlst;

	nlst = (t_list *)malloc(sizeof(t_list));
	if (!nlst)
		return (NULL);
	nlst->content = content;
	nlst->next = NULL;
	return (nlst);
}
