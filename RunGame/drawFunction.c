/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawFunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:27:47 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/07 10:36:42 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	dda_wall(t_cub3d game, int color)
{
	double	delta_x;
	double	delta_y;
	double	x_inc;
	double	y_inc;
	double	length;

	delta_x = game.dda.x2 - game.dda.x1;
	delta_y = game.dda.y2 - game.dda.y1;
	if (fabs(delta_x) > fabs(delta_y))
		length = fabs(delta_x);
	else
		length = fabs(delta_y);
	x_inc = delta_x / length;
	y_inc = delta_y / length;
	while (length-- > 0)
	{
		my_mlx_pixel_put(&game.img, game.dda.x1, game.dda.y1, color);
		game.dda.x1 += x_inc;
		game.dda.y1 += y_inc;
	}
}
