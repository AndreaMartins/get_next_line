/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:07:15 by andmart2          #+#    #+#             */
/*   Updated: 2023/06/06 19:48:15 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_and_store(int fd, char *store)
{
	char	*store_buffer;
	int		bytes_read;
	
	bytes_read = 1;
	store_buffer = malloc((BUFFER_SIZE + 1) sizeof(char));
	if (!store_buffer)
	{
		free(store_buffer);
		return(NULL);
	}
	//mientras no encuentre un salto de linea y los bytes leides sean direntes de cero
	while(!ft_strrchr(store, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		//cuando no existe
		if (bytes_read == -1)
			return (free_all(&store, &store_buffe));
		//cuando si existe y lo ha leido bien
		if (bytes_read != 0)
		{
			//cierra el string
			store_buffer[bytes_read] = '\0';
			//une el buffer string con lo que ya se tenia
			store = ft_strjoin(store, store_buffer);
		}
	}
	free(store_buffer);
	return(store);
}

char *get_next_line(int fd)
{
	char *line;
	char static *store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	store = read_and_store(fd, store);
	if(!store)
		return(NULL);

}
