/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawFunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:27:47 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/29 20:57:00 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	dda(t_cub3d game,int color)
{
	double	delta_x;
	double	delta_y;
	double	x_inc;
	double	y_inc;
	double	length;
	int		i;

	i = 0;
	delta_x = game.dda.x2 - game.dda.x1;
	delta_y = game.dda.y2 - game.dda.y1;
	if (fabs(delta_x) > fabs(delta_y))
		length = delta_x;
	else
		length = delta_y;
	x_inc = delta_x / length;
	y_inc = delta_y / length;
	while (i < length)
	{
		puts("here");
		my_mlx_pixel_put(&game.img, round(game.dda.x1), round(game.dda.y1), color);
		game.dda.x1 += x_inc;
		game.dda.y1 += y_inc;
		i++;
	}
}

void	draw_line(t_cub3d *game, int x, int y, int color)
{
	game->dda.x1 = x;
	game->dda.y1 = y;
	game->dda.x2 = cos(game->player.rotation_angle) * 40 + x;
	game->dda.y2 = sin(game->player.rotation_angle) * 40 + y;
	dda(*game, color);
}

void	draw_player(t_cub3d game)
{
	int		y;
	int		x;
	int		x_player;
	int		y_player;
	
	y = 0;
	y_player = game.player.y - game.map_info.tile_size / 4;
	x_player = game.player.x - game.map_info.tile_size / 4;
	while (y < game.map_info.tile_size / 2)
	{
		x = 0;
		while (x < game.map_info.tile_size / 2)
		{
			my_mlx_pixel_put(&game.img, x_player + x, y_player + y, RED);
			x++;
		}
		y++;
	}
}

void	put_square(t_cub3d game, int x_pixel, int y_pixel, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < game.map_info.tile_size)
	{
		x = 0;
		while (x < game.map_info.tile_size)
		{
			my_mlx_pixel_put(&game.img, x_pixel + x, y_pixel + y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_cub3d game)
{
	int x_pixel;
	int y_pixel;

	game.map_info.y = 0;
	game.map_info.x = 0;
	y_pixel = 0;
	x_pixel = 0;
	while (game.pars.map[game.map_info.y])
	{
		game.map_info.x = 0;
		x_pixel = 0;
		while (game.pars.map[game.map_info.y][game.map_info.x])
		{
			if (game.pars.map[game.map_info.y][game.map_info.x] == '1')
				put_square(game, x_pixel, y_pixel, WHITE);
			else if (game.pars.map[game.map_info.y][game.map_info.x] == '0')
				put_square(game, x_pixel, y_pixel, BLACK);
			x_pixel += game.map_info.tile_size;
			game.map_info.x++;
		}
		y_pixel += game.map_info.tile_size;
		game.map_info.y++;
	}
}