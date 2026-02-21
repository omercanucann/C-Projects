/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:38 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:39 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_word_size(char *str, int status)
{
	char	*temp_str;
	char	check_q;
	int		word_size;

	word_size = 0;
	temp_str = str;
	if (status == DNAIL || status == SNAIL)
	{
		check_q = *temp_str;
		temp_str++;
		while (*temp_str != '\0' && *temp_str != check_q)
		{
			word_size++;
			temp_str++;
		}
	}
	else if (status == DEFAULT)
	{
		while (is_word_delimiter(*temp_str) != 1)
		{
			word_size++;
			temp_str++;
		}
	}
	return (word_size);
}

char	*quote_word_save(t_token **token_list, char *str, char q_type)
{
	char	*word;
	int		type;
	char	*temp;
	int		merge;
	char	*start_temp;

	temp = malloc(sizeof(char) * (calculate_word_size(str, 1) + 1));
	start_temp = temp;
	type = check_operator_type(str);
	str++;
	while (*str != q_type && *str != '\0')
	{
		*temp = *str;
		temp++;
		str++;
	}
	if (*str == q_type)
		str++;
	*temp = '\0';
	merge = (*str != ' ' && *str != '\t' && *str != '\0');
	word = ft_strdup(start_temp);
	free(start_temp);
	create_token(token_list, word, type, merge);
	free(word);
	return (str);
}

char	*word_save(t_token **token_list, char *str)
{
	char	*word;
	int		type;
	char	*temp;
	int		merge;
	char	*start_temp;

	temp = malloc(sizeof(char) * (calculate_word_size(str, 0) + 1));
	if (!temp)
		return (NULL);
	start_temp = temp;
	type = check_operator_type(str);
	while (is_word_delimiter(*str) != 1)
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	merge = (*str != ' ' && *str != '\t' && *str != '\0');
	word = ft_strdup(start_temp);
	free(start_temp);
	create_token(token_list, word, type, merge);
	free(word);
	return (str);
}
