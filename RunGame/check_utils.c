/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:16:15 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 20:03:38 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	check_wall_collision(t_cub3d game)
{
	double x;
	double y;

	y = 0;
	while (y < 1)
	{
		x = 0;
		while (x < 1)
		{
			if (game.pars.map[(int)((game.player.back_y + y) \
				/ game.info.tile_size)][(int)((game.player.back_x + x) \
					/ game.info.tile_size)] == '1') 
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}