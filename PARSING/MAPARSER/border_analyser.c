/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:00:36 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/30 19:18:26 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

int	getheight(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

int	lastline(t_gamedata *data)
{
	int		i;
	char	c;
	int		height;

	i = 0;
	height = getheight(data->map) - 1;
	while (data->map[height][i])
	{
		c = data->map[height][i];
		if (c != '1' && c != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	firstline(t_gamedata *data)
{
	int		i;
	char	c;

	i = 0;
	while (data->map[0][i])
	{
		c = data->map[0][i];
		if (c != '1' && c != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	handleborder(t_gamedata *data)
{
	if (!firstline(data) || !lastline(data))
	{
		claimgamedata(data);
		display_error("Error : First/Last Line in map not valid");
	}
	handlstart(data);
	handlmax(data);
}
