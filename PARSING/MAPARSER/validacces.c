/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validacces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:49:12 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/28 19:51:28 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void    clone_mapgame(t_gamedata *data,  t_playerinfo *pos)
{
    int i;
    
    pos->clonedmap = malloc(sizeof(char *) * pos->height);
    i = -1;
    while(data->map[++i])
        pos->clonedmap[i] = reallocer(ft_strdup(data->map[i]), pos->tall_line + 1);
    pos->clonedmap[i] = NULL;
}

void    find_fill(t_gamedata *data, t_playerinfo *pos)
{
    int line;
    int column;
    char c;

    line = -1;
    pos->tall_line = ft_strlen(data->map[0]);
    while(data->map[++line])
    {
        if (ft_strlen(data->map[line]) > pos->tall_line)
            pos->tall_line = ft_strlen(data->map[line]) + 1;
        column = -1;
        while(data->map[line][++column])
        {
            c = data->map[line][column];
            if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
            {
                pos->player_x = column;
                pos->player_y = line;
            }
            if (c == ' ')
                pos->countspace++;
        }
    }
    pos->height = line + 1;
}

void player_acces(t_gamedata *data, t_playerinfo *pos)
{
    find_fill(data, pos);
    clone_mapgame(data, pos);
    check_recursivly(data, pos, pos->player_y, pos->player_x);
    int i;
    i = 0;
    while(pos->clonedmap[i])
        printf("%s\n", pos->clonedmap[i++]);
}

void    init_pos(t_playerinfo *pos)
{
    pos->clonedmap = NULL;
    pos->player_x = 0;
    pos->player_y = 0;
    pos->tall_line = 0;
    pos->countspace = 0;
    pos->height = 0;
}

void   _norequiredacces(t_gamedata *data)
{
    t_playerinfo pos;

    init_pos(&pos);
    player_acces(data,&pos);
}
