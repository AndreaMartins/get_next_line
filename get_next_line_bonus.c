/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:21:12 by andmart2          #+#    #+#             */
/*   Updated: 2023/06/15 12:47:54 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_two_str(char **s1, char **s2)
{
	if (*s1)
	{
		free (*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free (*s2);
		*s2 = NULL;
	}
	return (NULL);
}

char	*get_one_line(char *store)
{
	int		i;
	char	*line_extracted;

	i = 0;
	if (!store[i])
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	if (store [i] == '\n')
		i++;
	line_extracted = malloc((i + 1) * sizeof(char));
	if (!line_extracted)
		return (NULL);
	i = 0;
	while (store[i] && store[i] != '\n')
	{
		line_extracted[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
		line_extracted[i++] = '\n';
	line_extracted[i] = '\0';
	return (line_extracted);
}

char	*read_and_store(int fd, char *store)
{
	char	*store_buffer;
	int		bytes_read_counter;

	bytes_read_counter = 1;
	store_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!store_buffer)
	{
		free(store);
		return (NULL);
	}
	while (!ft_strchr(store, '\n') && bytes_read_counter != 0)
	{
		bytes_read_counter = read(fd, store_buffer, BUFFER_SIZE);
		if (bytes_read_counter == -1)
			return (free_two_str(&store, &store_buffer));
		if (bytes_read_counter != 0)
		{
			store_buffer[bytes_read_counter] = '\0';
			store = ft_strjoin(store, store_buffer);
		}
	}
	free(store_buffer);
	return (store);
}

char	*save_the_rest(char *store)
{
	int		i;
	int		j;
	char	*the_rest;

	i = 0;
	j = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (store && !store[i])
	{
		free(store);
		return (NULL);
	}
	the_rest = malloc((ft_strlen(store) - i + 1) * sizeof(char));
	if (!the_rest)
	{
		free(store);
		return (NULL);
	}
	i++;
	while (store[i] != '\0')
		the_rest[j++] = store[i++];
	the_rest[j] = '\0';
	free(store);
	return (the_rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*store[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = read_and_store(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	line = get_one_line(store[fd]);
	if (!line)
	{
		free(store[fd]);
		store[fd] = NULL;
	}
	else
		store[fd] = save_the_rest(store[fd]);
	return (line);
}
