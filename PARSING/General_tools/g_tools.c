/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:02:00 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/30 19:01:03 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	lens;

	lens = ft_strlen(src);
	if (size == 0)
		return (lens);
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lens);
}

int	getstart(char *data)
{
	int	start;

	start = 0;
	while (data[start] && (data[start] == ' ' || data[start] == '\t'))
		start++;
	return (start);
}

int	getend(char *data)
{
	size_t	end;

	end = ft_strlen(data) - 1;
	while (end >= 0 && (data[end] == ' ' || data[end] == '\t'
			|| data[end] == '\n'))
		end--;
	return (end);
}

char	*ft_strtrim(char *to_trim)
{
	t_trim	elem;

	elem.i = 0;
	elem.start_trim = getstart(to_trim);
	elem.end_trim = getend(to_trim);
	elem.trim_len = elem.end_trim - elem.start_trim;
	elem.trimmed = malloc(sizeof(char) * (elem.trim_len + 2));
	if (!elem.trimmed)
		return (NULL);
	while (to_trim[elem.start_trim] && elem.start_trim <= elem.end_trim)
	{
		elem.trimmed[elem.i] = to_trim[elem.start_trim];
		elem.i++;
		elem.start_trim++;
	}
	elem.trimmed[elem.i] = '\0';
	free(to_trim);
	return (epur_string(elem.trimmed));
}

char	*ft_strndup(char *to_dup, int len)
{
	int		i;
	char	*duped;

	if (!to_dup)
		return (NULL);
	i = 0;
	duped = malloc(sizeof(char) * (len + 1));
	if (!duped)
		return (NULL);
	while (to_dup[i] && i < len)
	{
		duped[i] = to_dup[i];
		i++;
	}
	duped[i] = '\0';
	return (duped);
}
