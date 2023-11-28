/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_begin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:29:35 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/28 18:30:56 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void    updown_checker(t_gamedata *data, int i, int firstone)
{
    while (firstone >= 0)
    {
        if ((data->map[i - 1][firstone] == '0' ) || data->map[i + 1][firstone] == '0')
            {
                claimgamedata(data);
                display_error("Error : OPEN MAP <-Left");
            }
        firstone--;
    }
}

int firstun(char *map)
{
    int i;

    i = 0;
    while (map[i])
    {
        if (map[i] == '1')
            return (i);
        i++;
    }
    return (3);
}

void    verifybeginline(char *line,t_gamedata *data)
{
    int i;

    i = 0;
    while(line[i] && line[i] == ' ')
        i++;
    if(line[i] != '1')
    {
        write(2, &line[i], 1);
        claimgamedata(data);
        display_error(" : None 1 caractere at begin");
    }
}

void    handlstart(t_gamedata *data)
{
    int i;
    int firstone;

    i = 0;
    while(data->map[i])
    {
        verifybeginline(data->map[i], data);
        if (data->map[i][0] != '1')
        {
            firstone = firstun(data->map[i]);
            updown_checker(data, i, firstone - 1);
        }
        i++;
    }
}