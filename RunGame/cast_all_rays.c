/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:58:36 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/30 22:24:59 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	cast_ray(t_cub3d *game)
{
	int		h_wall_hit;
	int		v_wall_hit;

}

void	get_h_d_ray(t_cub3d *game, int rays_id)
{
	double	stepsx;
	double	stepsy;
	int		offset;
	
	offset = 1;
	game->rays[rays_id].hyintersection = (game->player.y / game->map_info.tile_size) * game->map_info.tile_size;
	game->rays[rays_id].hxintersection = game->player.x + ((game->rays[rays_id].hyintersection - game->player.y) / tan(game->rays[rays_id].ray_angle));
	stepsy = game->map_info.tile_size;
	if (sin(game->rays[rays_id].ray_angle) < 0)
	{
		stepsy *= -1;
		offset *= -1;
	}
	stepsx = stepsy / tan(game->rays[rays_id].ray_angle);
	while((game->rays[rays_id].vxintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].vxintersection / game->map_info.tile_size) < game->map_info.len_x && (game->rays[rays_id].vyintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].vyintersection / game->map_info.tile_size) < game->map_info.len_y)
	{
		if (game->pars.map[(int)((game->rays[rays_id].vyintersection + offset) / game->map_info.tile_size)][(int)((game->rays[rays_id].vxintersection + offset) / game->map_info.tile_size)] == 1)	
		{
			break ;
		}
			game->rays[rays_id].hxintersection = stepsx;
			game->rays[rays_id].hyintersection = stepsy;
	}
}

void	get_v_d_ray(t_cub3d *game, int rays_id)
{
	double	stepx;
	double	stepy;
	int		offset;

	offset = 1;
	game->rays[rays_id].vxintersection = floor(game->player.x) / game->map_info.tile_size * game->map_info.tile_size;
	game->rays[rays_id].vyintersection = game->player.y + ((game->rays[rays_id].vxintersection - game->player.x) / tan(game->rays[rays_id].ray_angle));
	if (cos(game->rays[rays_id].ray_angle) > 0)
		game->rays[rays_id].vxintersection += game->map_info.tile_size;
	stepx = game->map_info.tile_size;
	if (cos(game->rays[rays_id].ray_angle) < 0)
	{
		stepx *= -1;
		offset *= -1;
	}
	stepy = stepx * tan(game->rays[rays_id].ray_angle);
	while((game->rays[rays_id].vxintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].vxintersection / game->map_info.tile_size) < game->map_info.len_x && (game->rays[rays_id].vyintersection / game->map_info.tile_size) >= 0 && (game->rays[rays_id].vyintersection / game->map_info.tile_size) < game->map_info.len_y)
	{
		if (game->pars.map[(int)((game->rays[rays_id].vyintersection + offset) / game->map_info.tile_size)][(int)((game->rays[rays_id].vxintersection + offset) / game->map_info.tile_size)] == 1)
		{
			break;
		}
		game->rays[rays_id].vxintersection += stepx;
		game->rays[rays_id].vyintersection += stepy;
	}
}

void	cast_all_rays(t_cub3d *game)
{
	int		rays_id;
	
	rays_id = 0;
	game->rays[rays_id].ray_angle = game->player.rotation_angle;
	while (rays_id < 1)
	{
		// get_h_d_ray(game, rays_id);
		get_v_d_ray(game, rays_id);
		

			// game->dda.x2 = game->rays[rays_id].hxintersection;
			// game->dda.y2 = game->rays[rays_id].hyintersection;
			// dda(*game, RED);
			game->dda.x2 = game->rays[rays_id].vxintersection;
			game->dda.y2 = game->rays[rays_id].vyintersection;
			dda(*game, GREEN);
		rays_id++;
		game->rays[rays_id].ray_angle += game->player.field_of_view / game->num_rays;
	}
}
