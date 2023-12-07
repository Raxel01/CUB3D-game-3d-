/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:50 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/07 10:27:07 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	get_color(t_texture texture, int x, int y)
{
	char	*dst;

	dst = texture.addr + (y * texture.line_length + \
			x * (texture.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	tex_render(t_cub3d *game, double wall_heightb, int rays_id, int side)
{
	double	distance_from_top;
	int		y;

	y = game->dda.y1;
	while (y < game->dda.y2)
	{
		distance_from_top = y + ((wall_heightb / 2) - (game->height / 2));
		game->texture->offset_y = distance_from_top * \
			(game->texture[side].height / wall_heightb);
		my_mlx_pixel_put(&game->img, rays_id, y, \
			get_color(game->texture[side], game->texture->offset_x, \
			game->texture->offset_y));
		y++;
	}
}

void	calcule_distance_of_ray(t_cub3d *game)
{
	get_h_i_ray(game);
	get_v_i_ray(game);
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
			h_wall(game, plane_d, rays_id);
		else
			v_wall(game, plane_d, rays_id);
		game->rays.ray_angle += game->player.field_of_view / game->num_rays;
		rays_id++;
	}
}
