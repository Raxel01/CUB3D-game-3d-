/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:58:36 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/02 20:15:46 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	get_h_d_ray(t_cub3d *game, int rays_id)
{
	double	stepx;
	double	stepy;
	int		offset;
	
	offset = 0;
	game->rays[rays_id].hyintersection = floor(game->player.y / game->map_info.tile_size) * game->map_info.tile_size;
	if (sin(game->rays[rays_id].ray_angle) > 0)
		game->rays[rays_id].hyintersection += game->map_info.tile_size;
	game->rays[rays_id].hxintersection = (game->rays[rays_id].hyintersection - game->player.y) / tan(game->rays[rays_id].ray_angle) + game->player.x;
	stepy = game->map_info.tile_size;
	if (sin(game->rays[rays_id].ray_angle) < 0)
	{
		stepy *= -1;
		offset = 1;
	}
	else if (sin(game->rays[rays_id].ray_angle) == 0)
		stepy = 0;
	stepx = stepy / tan(game->rays[rays_id].ray_angle);
	while((game->rays[rays_id].hxintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].hxintersection / game->map_info.tile_size) < game->map_info.len_x && (game->rays[rays_id].hyintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].hyintersection / game->map_info.tile_size) < game->map_info.len_y)
	{
		if (game->pars.map[(int)((game->rays[rays_id].hyintersection - offset) / game->map_info.tile_size)][(int)((game->rays[rays_id].hxintersection) / game->map_info.tile_size)] == '1')
			break;
		game->rays[rays_id].hxintersection += stepx;
		game->rays[rays_id].hyintersection += stepy;
	}
}

void	get_v_d_ray(t_cub3d *game, int rays_id)
{
	double	stepx;
	double	stepy;
	int		offset;

	offset = 0;
	game->rays[rays_id].vxintersection = (floor(game->player.x / game->map_info.tile_size)) * game->map_info.tile_size;
	if (cos(game->rays[rays_id].ray_angle) > 0)
		game->rays[rays_id].vxintersection += game->map_info.tile_size;
	game->rays[rays_id].vyintersection = (game->rays[rays_id].vxintersection - game->player.x) * tan(game->rays[rays_id].ray_angle) + game->player.y;
	stepx = game->map_info.tile_size;
	if (cos(game->rays[rays_id].ray_angle) < 0)
	{
		stepx *= -1;
		offset = 1;
	}
	else if (cos(game->rays[rays_id].ray_angle) == 0)
		stepx = 0;
	stepy = stepx * tan(game->rays[rays_id].ray_angle);
	while((game->rays[rays_id].vxintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].vxintersection / game->map_info.tile_size) < game->map_info.len_x && (game->rays[rays_id].vyintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].vyintersection / game->map_info.tile_size) < game->map_info.len_y)
	{
		if (game->pars.map[(int)((game->rays[rays_id].vyintersection) / game->map_info.tile_size)][(int)((game->rays[rays_id].vxintersection - offset) / game->map_info.tile_size)] == '1')
			break;
		game->rays[rays_id].vxintersection += stepx;
		game->rays[rays_id].vyintersection += stepy;
	}
}

void	cast_all_rays(t_cub3d *game)
{
	int		rays_id;
	
	rays_id = 0;
	game->rays[rays_id].ray_angle = game->player.rotation_angle - (game->player.field_of_view / 2);
	while (rays_id < game->num_rays)
	{
		get_h_d_ray(game, rays_id);
		get_v_d_ray(game, rays_id);
		game->rays[rays_id].hit_d_h = sqrt(pow(game->rays[rays_id].hxintersection - game->player.x, 2) + pow(game->rays[rays_id].hyintersection - game->player.y, 2));
		game->rays[rays_id].hit_d_v = sqrt(pow(game->rays[rays_id].vxintersection - game->player.x, 2) + pow(game->rays[rays_id].vyintersection - game->player.y, 2));
		if (game->rays[rays_id].hit_d_h < game->rays[rays_id].hit_d_v)
		{
			game->dda.x2 = game->rays[rays_id].hxintersection;
			game->dda.y2 = game->rays[rays_id].hyintersection;
			// dda(*game, GREY);
		}
		else
		{
			game->dda.x2 = game->rays[rays_id].vxintersection;
			game->dda.y2 = game->rays[rays_id].vyintersection;
			// dda(*game, GREY);
		}
		game->rays[rays_id + 1].ray_angle = game->rays[rays_id].ray_angle;
		game->rays[++rays_id].ray_angle += game->player.field_of_view / game->num_rays;
	}
}
