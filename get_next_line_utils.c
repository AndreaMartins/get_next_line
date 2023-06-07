/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmart2 <andmart2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:08:29 by andmart2          #+#    #+#             */
/*   Updated: 2023/06/06 19:57:00 by andmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strjoin(const char *s1, const char *s2)
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
}

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	cc;

	cc = (char) c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == cc)
		{
			return ((char *) &s[len]);
		}
		len --;
	}
	return (NULL);
}
