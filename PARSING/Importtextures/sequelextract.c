/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequelextract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:29:51 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/04 14:02:39 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	east_link(t_gamedata *data, char *line)
{
	int		j;
	char	*identifier;

	j = 0;
	while (line[j] && line[j] != ' ' && line[j] != '\t')
		j++;
	identifier = ft_strndup(line, j);
	if (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (!cmp_textures(identifier, "EA"))
	{
		free(identifier);
		addmember(&data->texture, build_member(ft_strndup(line + j,
					ft_strlen(line) - j), EAST));
	}
	else
	{
		free(identifier);
		write(2, "EA: IDENTIFIER ERROR\n", 21);
		throwtextures(line, data);
	}
}

/*check if the file exist if not -> acces == -1 Error*/
void	textureaccessiblity(t_gamedata *data)
{
	t_textures	*curs;
	int			acces;

	acces = 0;
	curs = data->texture;
	while (curs)
	{
		acces = open(curs->path, O_RDONLY, 0666);
		if (acces == -1)
		{
			write(2, curs->path, ft_strlen(curs->path));
			error(" : Inaccessible Texture");
			free_textures(&data->texture);
			free_color(&data->color);
			close(data->fd);
			display_error("");
		}
		close(acces);
		curs = curs->next;
	}
}

int	getspaces(char *line)
{
	int	whitespaces;
	int	i;

	i = 0;
	whitespaces = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			whitespaces++;
		if (line[i] == '\'')
			i = skipcontent(line, i, '\'');
		if (line[i] == '\"')
			i = skipcontent(line, i, '\"');
		i++;
	}
	return (whitespaces);
}

void	required_textures(t_gamedata *data)
{
	if (!data->texture || data->texture->size != 4)
	{
		free_textures(&data->texture);
		free_color(&data->color);
		close(data->fd);
		write(2, "Required: 4 textures", 20);
		write(2, "(EA WE SO NO)\n", 14);
		display_error("\tERROR OCCURED : NO ENOUGH TEXTURES");
	}
}
