/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:58:36 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/07 10:31:05 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	find_horizontal_intersection(t_cub3d *game, double stepy, \
	double stepx, int offset)
{
	while ((game->rays.hxinter / game->info.tile_size) >= 0 && \
		(game->rays.hxinter / game->info.tile_size) < game->info.len_x && \
		(game->rays.hyinter / game->info.tile_size) >= 0 && \
		(game->rays.hyinter / game->info.tile_size) < game->info.len_y)
	{
		if (game->pars.map[(int)((game->rays.hyinter - offset) / \
			game->info.tile_size)][(int)((game->rays.hxinter) / \
			game->info.tile_size)] == '1')
			break ;
		game->rays.hxinter += stepx;
		game->rays.hyinter += stepy;
	}
}

void	find_vertical_intersection(t_cub3d *game, double stepy, \
	double stepx, int offset)
{
	while ((game->rays.vxinter / game->info.tile_size) >= 0 && \
		(game->rays.vxinter / game->info.tile_size) < game->info.len_x && \
		(game->rays.vyinter / game->info.tile_size) >= 0 && (game->rays.vyinter \
		/ game->info.tile_size) < game->info.len_y)
	{
		if (game->pars.map[(int)((game->rays.vyinter) / \
			game->info.tile_size)][(int)((game->rays.vxinter - offset) / \
			game->info.tile_size)] == '1')
			break ;
		game->rays.vxinter += stepx;
		game->rays.vyinter += stepy;
	}
}

void	get_h_i_ray(t_cub3d *game)
{
	double	stepx;
	double	stepy;
	int		offset;

	offset = 0;
	game->rays.hyinter = floor(game->player.y / game->info.tile_size) * \
		game->info.tile_size;
	if (sin(game->rays.ray_angle) > 0)
		game->rays.hyinter += game->info.tile_size;
	game->rays.hxinter = (game->rays.hyinter - game->player.y) / \
		tan(game->rays.ray_angle) + game->player.x;
	stepy = game->info.tile_size;
	if (sin(game->rays.ray_angle) < 0)
	{
		stepy *= -1;
		offset = 1;
	}
	else if (sin(game->rays.ray_angle) == 0)
		stepy = 0;
	stepx = stepy / tan(game->rays.ray_angle);
	find_horizontal_intersection(game, stepy, stepx, offset);
}

void	get_v_i_ray(t_cub3d *game)
{
	double	stepx;
	double	stepy;
	int		offset;

	offset = 0;
	game->rays.vxinter = (floor(game->player.x / game->info.tile_size)) * \
		game->info.tile_size;
	if (cos(game->rays.ray_angle) > 0)
		game->rays.vxinter += game->info.tile_size;
	game->rays.vyinter = (game->rays.vxinter - game->player.x) * \
		tan(game->rays.ray_angle) + game->player.y;
	stepx = game->info.tile_size;
	if (cos(game->rays.ray_angle) < 0)
	{
		stepx *= -1;
		offset = 1;
	}
	else if (cos(game->rays.ray_angle) == 0)
		stepx = 0;
	stepy = stepx * tan(game->rays.ray_angle);
	find_vertical_intersection(game, stepy, stepx, offset);
}
