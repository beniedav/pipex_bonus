/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <badou@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:30:29 by badou             #+#    #+#             */
/*   Updated: 2025/05/12 20:01:21 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*fill_buffer_gnl(int fd, char *buff_str)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	bytes_read = 42;
	while (!gnl_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (buff_str)
				free(buff_str);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		buff_str = gnl_strjoin(buff_str, buffer);
		if (!buff_str)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (buff_str);
}

char	*fill_result(char *buff_str)
{
	size_t	i;
	char	*result;

	i = 0;
	while (buff_str[i] && buff_str[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (buff_str[i] && buff_str[i] != '\n')
	{
		result[i] = buff_str[i];
		i++;
	}
	if (buff_str[i] && buff_str[i] == '\n')
	{
		result[i] = buff_str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*handle_leftover(char *buff_str)
{
	char	*leftovers;
	size_t	i;
	size_t	j;

	i = 0;
	while (buff_str[i] && buff_str[i] != '\n')
		i++;
	if (!buff_str[i])
	{
		free(buff_str);
		return (NULL);
	}
	i++;
	leftovers = (char *)malloc(sizeof(char) * (gnl_strlen(buff_str) - i + 1));
	if (!leftovers)
	{
		free(buff_str);
		return (NULL);
	}
	j = 0;
	while (buff_str[i])
		leftovers[j++] = buff_str[i++];
	leftovers[j] = '\0';
	free(buff_str);
	return (leftovers);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buff_str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buff_str);
		buff_str = NULL;
		return (NULL);
	}
	result = NULL;
	buff_str = fill_buffer_gnl(fd, buff_str);
	if (!buff_str)
		return (NULL);
	result = fill_result(buff_str);
	if (!result)
		return (NULL);
	if (result[0] == '\0')
	{
		free(result);
		free(buff_str);
		buff_str = NULL;
		return (NULL);
	}
	buff_str = handle_leftover(buff_str);
	return (result);
}
