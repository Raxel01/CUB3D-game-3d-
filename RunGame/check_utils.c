/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:16:15 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/30 14:43:06 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	check_wall_collision(t_cub3d game)
{
	int x;
	int y;
	double x_pixel;
	double y_pixel;

	y_pixel = 0;
	x = (int)(game.player.back_x / game.map_info.tile_size);
	y = (int)(game.player.back_y / game.map_info.tile_size);
	while (y_pixel < 1)
	{
		x_pixel = 0;
		while (x_pixel < 1)
		{
			if (game.pars.map[(int)((game.player.back_y + y_pixel) / game.map_info.tile_size)][(int)((game.player.back_x + x_pixel) / game.map_info.tile_size)] == '1') 
				return (0);
			x_pixel++;
		}
		y_pixel++;
	}
	return (1);
}