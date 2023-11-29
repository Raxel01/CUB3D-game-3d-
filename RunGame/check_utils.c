/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:16:15 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/29 13:01:58 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	check_wall_collision(t_cub3d game)
{
	int x;
	int y;
	int x_pixel;
	int y_pixel;

	y_pixel = -2;
	x = (int)game.tmp.x / game.map_info.tile_size;
	printf("x = %f\n", game.tmp.x);
	y = (int)game.tmp.y / game.map_info.tile_size;
	printf("y = %d, x = %d\n", y, x);
	while (y_pixel < 2)
	{
		x_pixel = -2;
		while (x_pixel < 2)
		{
			// printf("%c\n", game.pars.map[y + y_pixel][x + x_pixel]);
			// printf("y = %d, x = %d\n", y + y_pixel, x + x_pixel);
			if (game.pars.map[y + y_pixel][x + x_pixel] == '1') 
				return (0);
			x_pixel++;
		}
		y_pixel++;
	}
	puts("okok");
	return (1);
}