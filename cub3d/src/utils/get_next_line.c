/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:13:32 by oucan             #+#    #+#             */
/*   Updated: 2025/11/26 20:26:33 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*readline_accumulate(int fd, char *readone)
{
	char	buff[BUFFER_SIZE + 1];
	int		count;
	char	*temp;

	count = 1;
	while (!ft_strchr(readone, '\n') && count != 0)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1)
		{
			free(readone);
			return (NULL);
		}
		buff[count] = '\0';
		temp = readone;
		readone = ft_strjoin(readone, buff);
		free(temp);
		if (!readone)
			return (NULL);
	}
	return (readone);
}

static char	*readline(int fd, char *readone)
{
	readone = readline_init(readone);
	if (!readone)
		return (NULL);
	return (readline_accumulate(fd, readone));
}

static char	*put(char *readone)
{
	char	*str;
	int		i;

	i = 0;
	if (!readone[i])
		return (NULL);
	while (readone[i] && readone[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (readone[i] && readone[i] != '\n')
	{
		str[i] = readone[i];
		i++;
	}
	if (readone[i] == '\n')
	{
		str[i] = readone[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*nextline(char *readone)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (readone[i] && readone[i] != '\n')
		i++;
	if (!readone[i])
	{
		free(readone);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(readone) - i + 1));
	if (!str)
	{
		free(readone);
		return (NULL);
	}
	i++;
	j = 0;
	while (readone[i])
		str[j++] = readone[i++];
	str[j] = '\0';
	free(readone);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*readone;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readone = readline(fd, readone);
	if (!readone)
		return (NULL);
	line = put(readone);
	readone = nextline(readone);
	return (line);
}
