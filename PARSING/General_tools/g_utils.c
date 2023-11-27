/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:57:50 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/26 21:32:53 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

long	ft_atoi(const char *str)
{
	long	i;
	long	lichara;
	long	natija;

	i = 0;
	lichara = 1;
	natija = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			lichara *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		natija = natija * 10 + str[i] - 48;
		i++;
	}
	return (natija * lichara);
}

int skipcontent(char *line, int i, char c)
{
    int start;

    start = i;
    i++;
    while (line[i] && line[i] != c)
        i++;
    if (!line[i])
        return (start);
    return (i);
}

int	cmp_textures(char *s1, char *s2)
{
	int	i;
	if (s1 == NULL)
		return (404);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL)
		return (404);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strrchr(char *str, int c)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen (str);
	if (c == '\0')
		return ((char *)(str + i));
	while (i >= 0)
	{
		if ((char )str[i] == (char)c)
		{
			if (*(str + i - 1))
				return ((char *)(str + i));
		}
		i--;
	}
	return (NULL);
}