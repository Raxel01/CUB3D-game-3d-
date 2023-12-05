/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:34:54 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 20:13:44 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	init_rays(t_cub3d *game)
{
	game->num_rays = game->width;
	game->rays.hit_d_h = 0;
	game->rays.hit_d_v = 0;
}

void	init_player(t_cub3d *game)
{
	game->player.is_up = 0;
	game->player.is_down = 0;
	game->player.is_right = 0;
	game->player.is_left = 0;
	game->player.is_turn_right = 0;
	game->player.is_turn_left = 0;
	game->player.walk_speed = 4;
	game->player.turn_speed = 0.1;
	game->player.field_of_view = 60 * (M_PI / 180);
}