/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:50 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/02 19:48:52 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	wall_rendring(t_cub3d *game)
{
	double	wall_projecion_height;
	double	distance_proj_plane;
	double	distance_from_wall;
	int		rays_id;
	
	rays_id = 0;
	while (rays_id < game->num_rays)
	{
		if (game->rays[rays_id].hit_d_h < game->rays[rays_id].hit_d_v)
			distance_from_wall = game->rays[rays_id].hit_d_h  * cos(game->rays[rays_id].ray_angle - game->player.rotation_angle);
		else
			distance_from_wall = game->rays[rays_id].hit_d_v  * cos(game->rays[rays_id].ray_angle - game->player.rotation_angle);
		
		distance_proj_plane = (game->width / 2) / tan(game->player.field_of_view / 2);
		wall_projecion_height = (game->map_info.tile_size / distance_from_wall) * distance_proj_plane;
		if (wall_projecion_height > game->height)
			wall_projecion_height = game->height;
		if (wall_projecion_height < 0)
			wall_projecion_height = 0;
		game->dda.x1 = rays_id;
		game->dda.y1 = (game->height / 2) - (wall_projecion_height / 2);
		game->dda.x2 = rays_id;
		game->dda.y2 = (game->height / 2) + (wall_projecion_height / 2);
		dda_wall(*game, GREENYELLOW);
		rays_id++;
	}
}
