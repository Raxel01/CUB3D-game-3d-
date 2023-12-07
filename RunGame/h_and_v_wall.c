/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_and_v_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:19:55 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/07 10:26:43 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	put_v_wall(t_cub3d *game, double wall_heightb, int rays_id)
{
	if (cos(game->rays.ray_angle) > 0)
	{
		game->texture->offset_x = fmod(game->rays.vyinter, \
			game->info.tile_size) * (game->texture[3].width / \
				game->info.tile_size);
		tex_render(game, wall_heightb, rays_id, 3);
	}
	else
	{
		game->texture->offset_x = (1 - fmod(game->rays.vyinter, \
			game->info.tile_size) / game->info.tile_size) * \
				game->texture[2].width;
		tex_render(game, wall_heightb, rays_id, 2);
	}
}

void	put_h_wall(t_cub3d *game, double wall_heightb, int rays_id)
{
	double	distance_from_top;

	if (sin(game->rays.ray_angle) < 0)
	{
		game->texture->offset_x = fmod(game->rays.hxinter, \
			game->info.tile_size) * (game->texture[0].width / \
				game->info.tile_size);
		tex_render(game, wall_heightb, rays_id, 0);
	}
	else
	{
		game->texture->offset_x = (1 - fmod(game->rays.hxinter, \
			game->info.tile_size) / game->info.tile_size) * \
				game->texture[1].width;
		tex_render(game, wall_heightb, rays_id, 1);
	}
}

void	v_wall(t_cub3d *game, double distance_proj_plane, int rays_id)
{
	double	wall_height;
	double	wall_heightb;
	int		distance_from_top;

	wall_height = (game->info.tile_size / (game->rays.hit_d_v * \
		cos(game->rays.ray_angle - game->player.rotation_angle))) * \
		distance_proj_plane;
	wall_heightb = wall_height;
	if (wall_height > game->height)
		wall_height = game->height;
	if (wall_height < 0)
		wall_height = 0;
	game->dda.x1 = rays_id;
	game->dda.y1 = (game->height / 2) - (wall_height / 2);
	game->dda.x2 = rays_id;
	game->dda.y2 = (game->height / 2) + (wall_height / 2);
	put_v_wall(game, wall_heightb, rays_id);
}

void	h_wall(t_cub3d *game, double distance_proj_plane, int rays_id)
{
	double	wall_height;
	double	wall_heightb;
	int		distance_from_top;

	wall_height = (game->info.tile_size / (game->rays.hit_d_h * \
		cos(game->rays.ray_angle - game->player.rotation_angle))) * \
		distance_proj_plane;
	wall_heightb = wall_height;
	if (wall_height > game->height)
		wall_height = game->height;
	if (wall_height < 0)
		wall_height = 0;
	game->dda.x1 = rays_id;
	game->dda.y1 = (game->height / 2) - (wall_height / 2);
	game->dda.x2 = rays_id;
	game->dda.y2 = (game->height / 2) + (wall_height / 2);
	put_h_wall(game, wall_heightb, rays_id);
}
