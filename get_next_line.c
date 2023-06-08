/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:07:15 by andmart2          #+#    #+#             */
/*   Updated: 2023/06/08 18:06:31 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


static char *free_two_str(char **s1,char **s2)
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
	int		bytes_read_counter;
	
	//para inicializar
	bytes_read_counter = 1;
	//espacio para amacenar la primera leida
	store_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	printf("en read|%i|\n", BUFFER_SIZE);
	if (!store_buffer)
	{
		free(store);
		return(NULL);
	}
	printf("buffer bien creado|%s|\n", store_buffer);
	//mientras no encuentre un salto de linea y los bytes leides sean direntes de cero
	while( !ft_strchr(store, '\n') && bytes_read_counter != 0)
	{
		printf("dentro del if|%s|\n", store);
		bytes_read_counter = read(fd, store_buffer, BUFFER_SIZE);
		printf("|%i|\n", bytes_read_counter);
		//cuando no existe
		if (bytes_read_counter == -1)
			return (free_two_str(&store, &store_buffer));
		//cuando si existe y lo ha leido bien
		if (bytes_read_counter != 0)
		{
			printf("|%i|\n", bytes_read_counter);
			//cierra el string
			store_buffer[bytes_read_counter] = '\0';
			printf("|%i|\n", bytes_read_counter);
			//une el store _buffer que acabo de leer al store (qen que parte esta el malloc del store nose)
			store = ft_strjoin(store, store_buffer);
			printf("buffer en store|%s|\n", store);
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
	//mientras exista store y no llegue al salto de linea que avance
	while(store[i] && store[i] != '\n')
		i++;
	//si existe el store y llego al final de la cadena
	if (store && !store[i])
	{
		free(store);
		return(NULL);
	}
	//cuando encontro un salto de linea creacion de espacio para el resto
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
	char		*line = "test aqui";
	//the first line found to return
	static char	*store = {0};
	//todo el troncho hasta encontrar el salto de linea en  encontrado static para usar en otros lados
	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	printf("hola");
	// guardar la lectura del buffer hasta que encuentre un salto de linea
	store = read_and_store(fd, store);
	printf("regreso|%s|\n", store);
	if(!store)
		return(NULL);
	//pasamos el store para conseguir la primera linea
	line = get_one_line(store);
	if (!line)
	{
		free (store);
		store = NULL;
	}
	//gestionar que se guarde el resto que queda de linea
	else
		store = save_the_rest(store);
		printf("|%s|\n", line);
	//se devuelve la linea
	return (line);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*the_line;
	int		i;

	if ( argc== 2 )
	{
		i = 0;
		fd = open((argv[1]), O_RDONLY);
		while (i < 2)
		{
			printf("==LECTURA== buffer_size:%d, %d lectura\n",BUFFER_SIZE,5);
			printf("=FD:%d=\n",fd);
			the_line  = get_next_line(fd);
			if (the_line != NULL)
				printf("bla|%s|\n", the_line);
			i++;
		}
		close(fd);	
	}
	return (0);
}
