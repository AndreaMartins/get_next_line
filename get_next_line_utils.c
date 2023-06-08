/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:08:29 by andmart2          #+#    #+#             */
/*   Updated: 2023/06/08 18:35:22 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

unsigned int	ft_strlen( const char *string)
{
	int	i;

	i = 0;
	while (string[i] != 0)
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
	{
		free (s1);
		return (NULL);
	}
	i = -1;
	j = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++j])
		s3 [i + j] = s2[j];
	s3[i + j] = '\0';
	if (s1)
		free(s1);
	return (s3);
}
/*char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*bigstring;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	bigstring = (char *)malloc(len_s1 + len_s2 + 1);
	if (!bigstring)
		return (NULL);
	while (i < len_s1)
	{
		bigstring[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		bigstring[i + j] = s2[j];
		j++;
	}
	bigstring[i + j] = '\0';
	return (bigstring);
}*/

/*char	*ft_strchr(char *s, int c)
{
	int		i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}*/
char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	/*if (c > 256)
		c %= 256;*/
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		++i;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}
