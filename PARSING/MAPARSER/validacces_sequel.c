/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validacces_sequel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:54:35 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/30 19:22:05 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	check_recursivly(t_gamedata *data, t_playerinfo *pos, int y, int x)
{
	if (x < 0 || y < 0 || x >= pos->tall_line || y >= pos->height - 1)
		return ;
	if (pos->clonedmap[y][x] == '1' || pos->clonedmap[y][x] == '#')
		return ;
	if (pos->clonedmap[y][x] == ' ')
	{
		pos->clonedmap = freearray(pos->clonedmap);
		claimgamedata(data);
		display_error("Error : Player have a Path to a space");
	}
	pos->clonedmap[y][x] = '#';
	check_recursivly(data, pos, y - 1, x);
	check_recursivly(data, pos, y + 1, x);
	check_recursivly(data, pos, y, x - 1);
	check_recursivly(data, pos, y, x + 1);
}

char	*fillcopy(char *dest, char *src, int size)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	while (i < size - 1)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
	free(src);
	return (dest);
}

char	*reallocer(char *line, int size)
{
	char	*new;

	new = malloc(sizeof(char) * size);
	if (!new)
		return (allocation_error(), NULL);
	new = fillcopy(new, line, size);
	return (new);
}
