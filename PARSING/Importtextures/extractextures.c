/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractextures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:23:30 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/23 19:38:14 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void    south_link(int fd, t_gamedata *data, char *line)
{
    int j;
    char *identifier;

    j = 0;
    while (line[j] && line[j] != ' ' && line[j] != '\t')
        j++;
    identifier = ft_strndup(line, j);
    if (line[j] && line[j] == ' ' || line[j] == '\t')
        j++;
    if (!cmp_textures(identifier, "SO"))
    {
        free(identifier);
        addmember(&data->texture, \
            build_member(ft_strndup(line + j, ft_strlen(line) - j), SOUTH));
    }
    else
    {
        free(identifier);
        write(2, "SO: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

void    nord_link(int fd, t_gamedata *data, char *line)
{
    int j;
    char *identifier;

    j = 0;
    while (line[j] && line[j] != ' ' && line[j] != '\t')
        j++;
    identifier = ft_strndup(line, j);
    if (line[j] && line[j] == ' ' || line[j] == '\t')
        j++;
    if (!cmp_textures(identifier, "NO"))
    {
        free(identifier);
        addmember(&data->texture, \
            build_member(ft_strndup(line + j, ft_strlen(line) - j), NORD));
    }
    else
    {
        free(identifier);
        write(2, "NO: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

/*TEXTURES GRAMMAR : [ID](SPCAE)[PATH]*/
/*COLOR GRAMMAR    :[ID](SPCAE)[R,G,B]*/
void    recognize_textures(int fd, t_gamedata *data, char *line)
{
    int     i;
    int     whitespaces;

    i = 0;
    line = ft_strtrim(line);
    whitespaces = getspaces(line);
    if (whitespaces == 1)
    {
        if (line[i] == 'N')
            nord_link(fd, data, line);
        else if (line[i] == 'S')
            south_link(fd, data, line);
        else if (line[i] == 'W')
            west_link(fd, data, line);
        else if (line[i] == 'E')
            east_link(fd, data, line);
        else
            recognize_color(fd, data, line);
        free(line);
    }
    else
        throwtextures(fd, line, data);
}

int validline(char *line)
{
    int i;

    if (line == NULL)
        return (1);
    i = 0;
    while(line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (1);
        i++;
    }
    return (0);
}

void    importtextures(int fd, t_gamedata *data)
{
    int     i;
    char    *line;

    i = 0;
    line = get_next_line(fd);
    while (line && i < 6)
    {
        if (validline(line))
        {
            recognize_textures(fd, data, line);
            i++;
        }
        else
            free(line);
        if(i == 6)
            break;
        line = get_next_line(fd);
    }
}