/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elemmap_analyser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:15:12 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/30 19:20:50 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	onlyplayer(t_gamedata *data)
{
	int	to_char;

	to_char = data->onlyplayers + 48;
	if (data->onlyplayers == 0 || data->onlyplayers > 1)
	{
		claimgamedata(data);
		write(2, &to_char, 1);
		display_error(" :<<- Players in map try with 1 player");
	}
}

int	diff(char c)
{
	return (c != '1' && c != '0' && c != 'N' && c != ' ' && c != 'W' && c != 'S'
		&& c != 'E');
}

int	playersign(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

void	elementanalyser(t_gamedata *data)
{
	int		line;
	int		column;
	char	c;

	line = 0;
	while (data->map[line])
	{
		column = 0;
		while (data->map[line][column])
		{
			c = data->map[line][column];
			if (diff(c))
			{
				write(2, &c, 1);
				claimgamedata(data);
				display_error(" :<<- ERROR : Weird element in The Map");
			}
			if (playersign(c))
				data->onlyplayers++;
			column++;
		}
		line++;
	}
}

void	mapanalyser(t_gamedata *data)
{
	elementanalyser(data);
	onlyplayer(data);
	handleborder(data);
	_norequiredacces(data);
}
