/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   claimmemory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:43:29 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/28 15:39:55 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void throwtextures(char *line, t_gamedata *data)
{
    free(line);
    free_textures(&data->texture);
    free_color(&data->color);
    close(data->fd);
    display_error("|- TEXTURES ERROR -|");
}

void    claimgamedata(t_gamedata *data)
{
    free_color(&data->color);
    free_textures(&data->texture);
    data->map = freearray(data->map);
    close(data->fd);
}

void	free_textures(t_textures **texture)
{
	t_textures	*cursur;

	while (*texture)
	{
		cursur = *texture;
		(*texture) = (*texture)->next;
		free(cursur->path);
		free(cursur);
	}
    (*texture) = NULL;
}

void    free_color(t_rgb **color)
{
    t_rgb	*cursur;

    while (*color)
	{
		cursur = *color;
		(*color) = (*color)->next;
		free(cursur->rgb);
		free(cursur);
	}
    (*color) = NULL;
}

char **freearray(char **array)
{
    int i;
    if (array == NULL)
        return (array);
    i = -1;
    while(array[++i])
        free(array[i]);
    free(array);
    array = NULL;
    return (array);
}
