/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:58:36 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 13:31:22 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	get_h_d_ray(t_cub3d *game)
{
	double	stepx;
	double	stepy;
	int		offset;
	
	offset = 0;
	game->rays.hyinter = floor(game->player.y / game->info.tile_size) * game->info.tile_size;
	if (sin(game->rays.ray_angle) > 0)
		game->rays.hyinter += game->info.tile_size;
	game->rays.hxinter = (game->rays.hyinter - game->player.y) / tan(game->rays.ray_angle) + game->player.x;
	stepy = game->info.tile_size;
	if (sin(game->rays.ray_angle) < 0)
	{
		stepy *= -1;
		offset = 1;
	}
	else if (sin(game->rays.ray_angle) == 0)
		stepy = 0;
	stepx = stepy / tan(game->rays.ray_angle);
	while((game->rays.hxinter / game->info.tile_size) >= 0 && (game->rays.hxinter / game->info.tile_size) < game->info.len_x && (game->rays.hyinter / game->info.tile_size) >= 0 && (game->rays.hyinter / game->info.tile_size) < game->info.len_y)
	{
		if (game->pars.map[(int)((game->rays.hyinter - offset) / game->info.tile_size)][(int)((game->rays.hxinter) / game->info.tile_size)] == '1')
			break;
		game->rays.hxinter += stepx;
		game->rays.hyinter += stepy;
	}
}

void	get_v_d_ray(t_cub3d *game)
{
	double	stepx;
	double	stepy;
	int		offset;

	offset = 0;
	game->rays.vxinter = (floor(game->player.x / game->info.tile_size)) * game->info.tile_size;
	if (cos(game->rays.ray_angle) > 0)
		game->rays.vxinter += game->info.tile_size;
	game->rays.vyinter = (game->rays.vxinter - game->player.x) * tan(game->rays.ray_angle) + game->player.y;
	stepx = game->info.tile_size;
	if (cos(game->rays.ray_angle) < 0)
	{
		stepx *= -1;
		offset = 1;
	}
	else if (cos(game->rays.ray_angle) == 0)
		stepx = 0;
	stepy = stepx * tan(game->rays.ray_angle);
	while((game->rays.vxinter / game->info.tile_size) >= 0 && (game->rays.vxinter / game->info.tile_size) < game->info.len_x && (game->rays.vyinter / game->info.tile_size) >= 0 && (game->rays.vyinter / game->info.tile_size) < game->info.len_y)
	{
		if (game->pars.map[(int)((game->rays.vyinter) / game->info.tile_size)][(int)((game->rays.vxinter - offset) / game->info.tile_size)] == '1')
			break;
		game->rays.vxinter += stepx;
		game->rays.vyinter += stepy;
	}
}

void	cast_all_rays(t_cub3d *game)
{
	int		rays_id;
	
	rays_id = 0;
	game->rays.ray_angle = game->player.rotation_angle - (game->player.field_of_view / 2);
	while (rays_id < game->num_rays)
	{
		get_h_d_ray(game);
		get_v_d_ray(game);
		game->rays.hit_d_h = sqrt(pow(game->rays.hxinter - game->player.x, 2) + pow(game->rays.hyinter - game->player.y, 2));
		game->rays.hit_d_v = sqrt(pow(game->rays.vxinter - game->player.x, 2) + pow(game->rays.vyinter - game->player.y, 2));
		if (game->rays.hit_d_h < game->rays.hit_d_v)
		{
			game->dda.x2 = game->rays.hxinter;
			game->dda.y2 = game->rays.hyinter;
		}
		else
		{
			game->dda.x2 = game->rays.vxinter;
			game->dda.y2 = game->rays.vyinter;
		}
		game->rays.ray_angle += game->player.field_of_view / game->num_rays;
		rays_id++;
	}
}
