/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractcolor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:33:25 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/06 14:58:06 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	west_link(t_gamedata *data, char *line)
{
	int		j;
	char	*identifier;

	j = 0;
	while (line[j] && line[j] != ' ' && line[j] != '\t')
		j++;
	identifier = ft_strndup(line, j);
	if (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (!cmp_textures(identifier, "WE"))
	{
		free(identifier);
		addmember(&data->texture, build_member(ft_strndup(line + j,
					ft_strlen(line) - j), WEST));
	}
	else
	{
		free(identifier);
		write(2, "WE: IDENTIFIER ERROR\n", 21);
		throwtextures(line, data);
	}
}

long	*verifygrammar(char *line, int index, t_gamedata *data)
{
	char	**rgb;

	rgb = ft_split(ft_strndup(line + index, ft_strlen(line) - index), ',', 1);
	return (rgb_status(rgb, line, data));
}

void	ceilingcolor(t_gamedata *data, char *line)
{
	int		index;
	char	*id;

	index = 0;
	while (line[index] && line[index] != ' ' && line[index] != '\t')
		index++;
	id = ft_strndup(line, index);
	if (line[index] && (line[index] == ' ' || line[index] == '\t'))
		index++;
	if (!cmp_textures(id, "C"))
	{
		free(id);
		linknodes(&data->color, creatnode(verifygrammar(line, index, data),
				CIEL));
	}
	else
	{
		free(id);
		write(2, "C: IDENTIFIER ERROR\n", 21);
		throwtextures(line, data);
	}
}

void	floorcolor(t_gamedata *data, char *line)
{
	int		index;
	char	*id;

	index = 0;
	while (line[index] && line[index] != ' ' && line[index] != '\t')
		index++;
	id = ft_strndup(line, index);
	if (line[index] && (line[index] == ' ' || line[index] == '\t'))
		index++;
	if (!cmp_textures(id, "F"))
	{
		free(id);
		linknodes(&data->color, creatnode(verifygrammar(line, index, data),
				FLOOR));
	}
	else
	{
		free(id);
		write(2, "F: IDENTIFIER ERROR\n", 21);
		throwtextures(line, data);
	}
}

void	recognize_color(t_gamedata *data, char *line)
{
	if (line[0] == 'F')
		floorcolor(data, line);
	else if (line[0] == 'C')
		ceilingcolor(data, line);
}
