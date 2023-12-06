/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onlyrequired.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:14:09 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/06 15:27:49 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	init_dir(t_direction *dir)
{
	dir->no = 0;
	dir->so = 0;
	dir->we = 0;
	dir->ea = 0;
	dir->f = 0;
	dir->c = 0;
}

int	only_elem(t_direction dir)
{
	return (dir.c != 1 || dir.f != 1 || dir.ea != 1 \
		|| dir.we != 1 || dir.no != 1 || dir.so != 1);
}

void	elemnt_diff(t_gamedata *data, t_direction dir)
{
	if (only_elem(dir))
	{
		free_textures(&data->texture);
		free_color(&data->color);
		close(data->fd);
		display_error("\tERROR : Duplicate elems[TEXT.. or color]");
	}
}

void	reqtextures(t_textures *curs, t_direction *dir)
{
	while (curs)
	{
		if (curs->type == NORD)
			dir->no++;
		else if (curs->type == SOUTH)
			dir->so++;
		else if (curs->type == EAST)
			dir->ea++;
		else if (curs->type == WEST)
			dir->we++;
		curs = curs->next;
	}
}

void	requiredelem(t_gamedata *data)
{
	t_direction	dir;
	t_textures	*curs;
	t_rgb		*rgcurs;

	init_dir(&dir);
	curs = data->texture;
	rgcurs = data->color;
	reqtextures(curs, &dir);
	while (rgcurs)
	{
		if (rgcurs->type == FLOOR)
			dir.f++;
		else if (rgcurs->type == CIEL)
			dir.c++;
		rgcurs = rgcurs->next;
	}
	elemnt_diff(data, dir);
}
