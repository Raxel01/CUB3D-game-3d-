/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractextures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:23:30 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/05 20:19:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	south_link(t_gamedata *data, char *line)
{
	int		j;
	char	*identifier;

	j = 0;
	while (line[j] && line[j] != ' ' && line[j] != '\t')
		j++;
	identifier = ft_strndup(line, j);
	if (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (!cmp_textures(identifier, "SO"))
	{
		free(identifier);
		addmember(&data->texture, build_member(ft_strndup(line + j,
					ft_strlen(line) - j), SOUTH));
	}
	else
	{
		free(identifier);
		write(2, "SO: IDENTIFIER ERROR\n", 21);
		throwtextures(line, data);
	}
}

void	nord_link(t_gamedata *data, char *line)
{
	int		j;
	char	*identifier;

	j = 0;
	while (line[j] && line[j] != ' ' && line[j] != '\t')
		j++;
	identifier = ft_strndup(line, j);
	if (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (!cmp_textures(identifier, "NO"))
	{
		free(identifier);
		addmember(&data->texture, build_member(ft_strndup(line + j,
					ft_strlen(line) - j), NORD));
	}
	else
	{
		free(identifier);
		write(2, "NO: IDENTIFIER ERROR\n", 21);
		throwtextures(line, data);
	}
}

/*TEXTURES GRAMMAR : [ID](SPCAE)[PATH]*/
/*COLOR GRAMMAR    :[ID](SPCAE)[R,G,B]*/
void	recognize_textures(t_gamedata *data, char *line)
{
	int	i;
	int	whitespaces;

	i = 0;
	line = ft_strtrim(line);
	whitespaces = getspaces(line);
	if (whitespaces == 1)
	{
		if (line[i] == 'N')
			nord_link(data, line);
		else if (line[i] == 'S')
			south_link(data, line);
		else if (line[i] == 'W')
			west_link(data, line);
		else if (line[i] == 'E')
			east_link(data, line);
		else
			recognize_color(data, line);
		free(line);
	}
	else
	{
		write(2, "Error: GRAMMAR-> [ID][SPACE][PATH/[r,g,b]]\n\t", 44);
		throwtextures(line, data);
	}
}

int	validline(char *line)
{
	int	i;

	if (line == NULL)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	importtextures(t_gamedata *data)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(data->fd);
	while (line && i < 6)
	{
		if (validline(line))
		{
			recognize_textures(data, line);
			i++;
		}
		else
			free(line);
		if (i == 6)
			break ;
		line = get_next_line(data->fd);
	}
}
