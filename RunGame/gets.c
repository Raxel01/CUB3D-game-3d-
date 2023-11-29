/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:33:27 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/29 12:02:19 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	get_player_position(t_cub3d *game)
{
	int x;
	int y;
	
	y = 0;
	while (game->pars.map[y])
	{
		x = 0;
		while (game->pars.map[y][x])
		{
			if (game->pars.map[y][x] == 'N' || game->pars.map[y][x] == 'S' ||
				game->pars.map[y][x] == 'E' || game->pars.map[y][x] == 'W')
			{
				game->player.x = (x * game->map_info.tile_size) + (game->map_info.tile_size / 2);
				game->player.y = (y * game->map_info.tile_size) + (game->map_info.tile_size / 2);
				return ;
			}
			x++;
		}
		y++;
	}
}