/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:16:02 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/20 11:54:10 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (s)
	{
		i = start;
		j = 0;
		str = (char *)malloc(sizeof(char) * (len +1));
		if (!str)
			return (NULL);
		while (s[i] && i < (len + start))
		{
			str[j++] = s[i++];
		}
		str[j] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strdup(char *s)
{
	char	*ptr;
	size_t	len ;
	size_t	i;

	len = ft_strlen(s) + 1;
	i = 0;
	ptr = (char *)malloc (len * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*join;
	int			i;
	int			j;
	int			len_s1;
	int			len_s2;

	if (!s1)
		return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *) malloc(len_s1 + len_s2 + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < len_s1)
		join[i] = s1[i];
	while (j < len_s2)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}

int	ft_strchr(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
