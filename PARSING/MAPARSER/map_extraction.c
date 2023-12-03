/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:53:47 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/03 11:50:52 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	mapstate(char *map, t_gamedata *data)
{
	int	elem;

	if (map == NULL)
	{
		claimgamedata(data);
		display_error("\tERROR : No map in File.cub recheck :]");
	}
}

char	*findmap(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (!validline(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	extractmap(t_gamedata *data)
{
	char	*line;
	char	*map;

	map = NULL;
	line = findmap(data->fd);
	while (line)
	{
		if (!validline(line))
		{
			claimgamedata(data);
			free(line);
			free(map);
			display_error("Error :Invalid line in map:");
		}
		else
		{
			map = ft_strjoin(map, line);
			free(line);
		}
		line = get_next_line(data->fd);
	}
	mapstate(map, data);
	data->map = ft_split(map, '\n', 0);
}
