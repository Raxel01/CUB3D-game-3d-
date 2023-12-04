/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:33:27 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/03 14:25:27 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	get_start_angle(t_cub3d *game, char player_direction)
{
	if (player_direction == 'N')
		game->player.rotation_angle = 270 * M_PI / 180;
	else if (player_direction == 'S')
		game->player.rotation_angle = 90 * M_PI / 180;
	else if (player_direction == 'E')
		game->player.rotation_angle = 0 * M_PI / 180;
	else if (player_direction == 'W')
		game->player.rotation_angle = 180 * M_PI / 180;
}

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
				get_start_angle(game, game->pars.map[y][x]);
				game->player.x = (x * game->map_info.tile_size) + (game->map_info.tile_size / 2);
				game->player.y = (y * game->map_info.tile_size) + (game->map_info.tile_size / 2);
				return ;
			}
			x++;
		}
		y++;
	}
}

// void	get_player_position(t_cub3d *game)
// {
// 	int x;
// 	int y;
	
// 	y = 0;
// 	while (game->pars.map[y])
// 	{
// 		x = 0;
// 		while (game->pars.map[y][x])
// 		{
// 			if (game->pars.map[y][x] == 'N' || game->pars.map[y][x] == 'S' ||
// 				game->pars.map[y][x] == 'E' || game->pars.map[y][x] == 'W')
// 			{
// 				get_start_angle(game, game->pars.map[y][x]);
// 				game->player.x = (x * game->map_info.tile_size) + (game->map_info.tile_size / 2);
// 				game->player.y = (y * game->map_info.tile_size) + (game->map_info.tile_size / 2);
// 				return ;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }