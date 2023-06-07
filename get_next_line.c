/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:07:15 by andmart2          #+#    #+#             */
/*   Updated: 2023/06/07 19:21:20 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


static char *free_all(char **s1,char **s2)
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
	return(NULL);
}

char *get_one_line(char *store)
{
	int i;
	char *line_extracted;

	i = 0;
	//si no existe devuelve null
	if (!store[i])
		return (NULL);
	//mientras exista y no llegue al salto de linea
	while (store[i] && store[i] != '\n')
		i++;
	//si hay el salto de linea aumenta el contador en uno 
	if (store [i] == '\n')
		i++;
	//se crea espacio para guardar en el malloc la nueva linea
	line_extracted = malloc((i + 1) * sizeof(char));
	if (!line_extracted)
		return(NULL);
	//si todo sale bien se almancena incluyendo o no el salto de linea
	i = 0;
	while(store[i])
	{
		line_extracted[i] = store[i];
		i++;
	}
	line_extracted[i] = '\0';
	return(line_extracted);
}

char *read_and_store(int fd, char *store)
{
	char	*store_buffer;
	int		bytes_read;
	
	bytes_read = 1;
	store_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!store_buffer)
	{
		free(store_buffer);
		return(NULL);
	}
	//mientras no encuentre un salto de linea y los bytes leides sean direntes de cero
	while(!ft_strrchr(store, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, store_buffer, BUFFER_SIZE);
		//cuando no existe
		if (bytes_read == -1)
			return (free_all(&store, &store_buffer));
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
	//devuelve el troncho hasta que encuentra un salto de linea
	return(store);
}

char *save_the_rest(char *store)
{
	int i;
	int j;
	char *the_rest;

	i = 0;
	j = 0;
	while(store[i] && store[i] != '\n')
		i++;
	if (store && !store[i])
	{
		free(store);
		return(NULL);
	}
	the_rest = malloc((ft_strlen(store) - i + 1) * sizeof(char));
	if (!the_rest)
	{
		free(the_rest);
		return(NULL);
	}
	//para saltar el caracter slato de linea
	i++;
	while (store[i] != '\0')
	{
		the_rest[j] = store[i];
		i++;
		j++;
	}
	the_rest[j] = '\0';
	free(store);
	return(the_rest);
}

char *get_next_line(int fd)
{
	printf("hi");
	char *line;
	//the first line found to return
	char static *store;
	//todo el troncho hasta encontrar el salto de linea en  encontrado static para usar en otros lados

	printf("hi");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	printf("hola");
	store = read_and_store(fd, store);
	printf("|%s|\n", store);
	if(!store)
		return(NULL);
	line = get_one_line(store);
	if (!line)
	{
		free (store);
		store = NULL;
	}
	else
		store = save_the_rest(store);
	printf("|%s|\n", line);
	
	return (line);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if ( argc== 2 )
	{
		i = 0;
		fd = open((argv[1]), O_RDONLY);
		while (i < 50)
		{
			printf("==LECTURA== buffer_size:%d, %d lectura\n",BUFFER_SIZE,i);
			printf("=FD:%d=\n",fd);
			line  = get_next_line(fd);
			if (line != NULL)
				printf("|%s|\n", line);
			i++;
		}
		close(fd);	
	}
	return (0);
}
