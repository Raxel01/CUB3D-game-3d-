/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:34:54 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/06 12:17:39 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	to_hex(long *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	
	return (r << 16 | g << 8 | b);
}

void	init_floor_ciel(t_cub3d *game)
{
	game->info.ceil_color = to_hex(game->pars.color->rgb);
	game->info.floor_color = to_hex(game->pars.color->next->rgb);
}

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