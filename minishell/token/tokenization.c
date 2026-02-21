/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:30:36 by oucan             #+#    #+#             */
/*   Updated: 2025/07/20 21:30:37 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_token **token_list, char *word,
					int type, int merge)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(word);
		return ;
	}
	fill_token(new_token, word, type, merge);
	add_back_token(token_list, new_token);
}

int	check_quote(char *str)
{
	int	status;

	status = DEFAULT;
	while (*str)
	{
		status = set_status(status, str);
		str++;
	}
	if (status != DEFAULT)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (1);
	}
	return (0);
}

int	tokenization(t_data *data, char *str)
{
	int	type;

	if (check_quote(str))
		return (1);
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (!*str)
			break ;
		type = seperator(str);
		if (type && type != SPACES && type != END)
			str = save_separator(&data->token, str, type);
		else
		{
			if (*str == '\"' || *str == '\'')
				str = quote_word_save(&data->token, str, *str);
			else
				str = word_save(&data->token, str);
		}
	}
	return (0);
}
