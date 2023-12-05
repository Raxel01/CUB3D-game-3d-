/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:16:15 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 20:51:17 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	check_wall_collision(t_cub3d game)
{
	int	x;
	int	y;

	y = -2;
	while (y < 2)
	{
		x = -2;
		while (x < 2)
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