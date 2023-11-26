/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_usage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:38:24 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/23 11:21:37 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

static int	ft_words(char const *s, char c)
{
	int	i;
	int	words;

	if (s[0] == '\0')
		return (0);
	words = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			words++;
		i++;
	}
	if (s[i - 1] != c)
		words++;
	return (words);
}

static char	*next_word(char *str, char c, int *len)
{
	int		i;
	char	*tmp;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && str[i] == c)
		i++;
	tmp = &str[i];
	while (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	*len = count;
	return (tmp);
}

static char	**ft_freetab(char **str, int tofree)
{
	while (--tofree >= 0)
		free(str[tofree]);
	free(str);
	str = NULL;
	return (str);
}

int check_comma(char *s)
{
    int i;
    int comma;

    comma = 0;
    i = 0;
    while(s[i])
    {
        if (s[i] == ',')
            comma++;
        i++;
    }
    return (comma);
}

/*if color = 1 then I check the color case*/
/*else if 0 I'm sing split for other things*/
char	**ft_split(char *s, char c, int color)
{
    t_split split;

	if (color == 1)
    	if (check_comma(s) != 2 || !s)
        	return(free(s), NULL);
	split.i = -1;
	split.words = ft_words(s, c);
	split.str = (char **)malloc(sizeof(char *) * (split.words + 1));
	if (!split.str)
		return (NULL);
	split.tmp = (char *)s;
	split.len = 0;
	while (++split.i < split.words)
	{
		split.tmp = next_word(split.tmp + split.len, c, &split.len);
		split.str[split.i] = (char *)malloc(split.len + 1);
		if (!split.str[split.i])
			return (ft_freetab(split.str, split.i));
		ft_strlcpy(split.str[split.i], split.tmp, split.len + 1);
	}
	split.str[split.i] = 0;
    free(s);
	return (split.str);
}
