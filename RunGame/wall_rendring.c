/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:50 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/06 18:57:26 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	is_facing_up(double ray_angle)
{
	if (sin(ray_angle) < 0)
		return (1);
	return (0);
}

int	is_facing_right(double ray_angle)
{
	if (cos(ray_angle) > 0)
		return (1);
	return (0);
}

int	get_color(t_texture texture, int x, int y)
{
	char	*dst;

	dst = texture.addr + (y * texture.line_length + \
			x * (texture.bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	draw_v_wall(t_cub3d *game, double distance_proj_plane, int rays_id)
{
	double	wall_height;
	double	wall_heightb;
	int		distance_from_top;
	int		y;

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
	y = game->dda.y1;
	if (is_facing_right(game->rays.ray_angle))
	{
		game->texture->offset_x = fmod(game->rays.vyinter, game->info.tile_size) * (game->texture[3].width / game->info.tile_size);
		while (y < game->dda.y2)
		{
			distance_from_top = y + ((wall_heightb / 2) - (game->height / 2));
			game->texture->offset_y = (distance_from_top * (float)game->texture[3].height) / wall_heightb;
			my_mlx_pixel_put(&game->img, rays_id, y, get_color(game->texture[3], game->texture->offset_x, game->texture->offset_y)); 
			y++;
		}
	}
	else
	{
		game->texture->offset_x = (1 - fmod(game->rays.vyinter, game->info.tile_size) / game->info.tile_size) * game->texture[2].width;
		while (y < game->dda.y2)
		{
			distance_from_top = y + ((wall_heightb / 2) - (game->height / 2));
			game->texture->offset_y = (distance_from_top * (float)game->texture[2].height) / wall_heightb;
			my_mlx_pixel_put(&game->img, rays_id, y, get_color(game->texture[2], game->texture->offset_x, game->texture->offset_y));
			y++;
		}
	}
}

void	draw_h_wall(t_cub3d *game, double distance_proj_plane, int rays_id)
{
	double	wall_height;
	double	wall_heightb;
	int		distance_from_top;
	int		y;
	
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
	y = game->dda.y1;
	if (is_facing_up(game->rays.ray_angle))
	{
		game->texture->offset_x = fmod(game->rays.hxinter, game->info.tile_size) * (game->texture[0].width / game->info.tile_size);
		while (y < game->dda.y2)
		{
			distance_from_top = y + ((wall_heightb / 2) - (game->height / 2));
			game->texture->offset_y = distance_from_top * (game->texture[0].height / wall_heightb);
			my_mlx_pixel_put(&game->img, rays_id, y, get_color(game->texture[0], game->texture->offset_x, game->texture->offset_y));
			y++;
		}
	}
	else
	{
		game->texture->offset_x = (1 - fmod(game->rays.hxinter, game->info.tile_size) / game->info.tile_size) * game->texture[2].width;
		while (y < game->dda.y2)
		{
			distance_from_top = y + ((wall_heightb / 2) - (game->height / 2));
			game->texture->offset_y = distance_from_top * (game->texture[1].height / wall_heightb);
			my_mlx_pixel_put(&game->img, rays_id, y, get_color(game->texture[1], game->texture->offset_x, game->texture->offset_y));
			y++;
		}
	}
}

void	calcule_distance_of_ray(t_cub3d *game)
{
	get_h_d_ray(game);
	get_v_d_ray(game);
	game->rays.hit_d_h = sqrt(pow(game->rays.hxinter - game->player.x, 2) \
		+ pow(game->rays.hyinter - game->player.y, 2));
	game->rays.hit_d_v = sqrt(pow(game->rays.vxinter - game->player.x, 2) \
		+ pow(game->rays.vyinter - game->player.y, 2));
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
		calcule_distance_of_ray(game);
		if (game->rays.hit_d_h < game->rays.hit_d_v)
			draw_h_wall(game, plane_d, rays_id);
		else
			draw_v_wall(game, plane_d, rays_id);
		game->rays.ray_angle += game->player.field_of_view / game->num_rays;
		rays_id++;
	}
}
