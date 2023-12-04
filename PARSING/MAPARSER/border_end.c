/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:32:59 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/03 12:05:47 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	upchecker(t_gamedata *data, int i, int firstone)
{
	if (i != 0)
	{
		if (data->map[i - 1][firstone] == '0')
		{
			claimgamedata(data);
			display_error("Error : OPEN MAP <-Left");
		}
	}
}

int	indexof_lastelem(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && line[i] == ' ')
		i--;
	return (i);
}

int	invalidzero(int column, t_gamedata *data, int line)
{
	return (column > (indexof_lastelem(data->map[line - 1]))
		|| column > (indexof_lastelem(data->map[line + 1])));
}

void	verifyendline(char *line, t_gamedata *data)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && line[i] == ' ')
		i--;
	if (line[i] != '1')
	{
		write(2, &line[i], 1);
		claimgamedata(data);
		write(2, " : None 1 caractere", 19);
		display_error(" at the end of line");
	}
}

void	handlmax(t_gamedata *data)
{
	int		line;
	int		column;
	char	hold;

	line = -1;
	while (data->map[++line])
	{
		verifyendline(data->map[line], data);
		column = -1;
		while (data->map[line][++column])
		{
			hold = data->map[line][column];
			if (hold == '0')
			{
				if (invalidzero(column, data, line))
				{
					claimgamedata(data);
					display_error("Error : OPEN MAP -> right");
				}
			}
		}
	}
}
