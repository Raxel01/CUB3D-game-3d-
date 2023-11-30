/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:34:54 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/30 15:02:19 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	init_rays(t_cub3d *game)
{
	
}

void	init_player(t_cub3d *game)
{
	game->player.is_up = 0;
	game->player.is_down = 0;
	game->player.is_right = 0;
	game->player.is_left = 0;
	game->player.is_turn_right = 0;
	game->player.is_turn_left = 0;
	game->player.walk_speed = 2;
	game->player.turn_speed = 0.1;
	game->player.rotation_angle = 0;
}