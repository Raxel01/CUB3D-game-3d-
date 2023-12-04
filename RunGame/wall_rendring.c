/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:50 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/04 18:29:17 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	draw_v_wall(t_cub3d *game, double distance_proj_plane, int rays_id)
{
	double	wall_height;

	wall_height = (game->map_info.tile_size / (game->rays.hit_d_v * \
		cos(game->rays.ray_angle - game->player.rotation_angle))) * \
		distance_proj_plane;
	if (wall_height > game->height)
		wall_height = game->height;
	if (wall_height < 0)
		wall_height = 0;
	game->dda.x1 = rays_id;
	game->dda.y1 = (game->height / 2) - (wall_height / 2);
	game->dda.x2 = rays_id;
	game->dda.y2 = (game->height / 2) + (wall_height / 2);
	dda_wall(*game, GREY);
}

void	draw_h_wall(t_cub3d *game, double distance_proj_plane, int rays_id)
{
	double	wall_height;

	wall_height = (game->map_info.tile_size / (game->rays.hit_d_h * \
		cos(game->rays.ray_angle - game->player.rotation_angle))) * \
		distance_proj_plane;
	if (wall_height > game->height)
		wall_height = game->height;
	if (wall_height < 0)
		wall_height = 0;
	game->dda.x1 = rays_id;
	game->dda.y1 = (game->height / 2) - (wall_height / 2);
	game->dda.x2 = rays_id;
	game->dda.y2 = (game->height / 2) + (wall_height / 2);
	dda_wall(*game, GREY);
}

void	wall_rendring(t_cub3d *game)
{
	int		rays_id;
	double	plane_d;

	rays_id = 0;
	plane_d = (game->width / 2) / tan(game->player.field_of_view / 2);
	game->rays.ray_angle = game->player.rotation_angle - \
		(game->player.field_of_view / 2);
	while (rays_id < game->num_rays)
	{
		get_h_d_ray(game);
		get_v_d_ray(game);
		game->rays.hit_d_h = sqrt(pow(game->rays.hxinter - game->player.x, 2) \
			+ pow(game->rays.hyinter - game->player.y, 2));
		game->rays.hit_d_v = sqrt(pow(game->rays.vxinter - game->player.x, 2) \
			+ pow(game->rays.vyinter - game->player.y, 2));
		if (game->rays.hit_d_h < game->rays.hit_d_v)
			draw_h_wall(game, plane_d, rays_id);
		else
			draw_v_wall(game, plane_d, rays_id);
		game->rays.ray_angle += game->player.field_of_view / game->num_rays;
		rays_id++;
	}
}
