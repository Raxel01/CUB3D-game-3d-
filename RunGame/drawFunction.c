/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawFunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:27:47 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 13:31:53 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	dda(t_cub3d game,int color)
{
	double	delta_x;
	double	delta_y;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	double	length;

	x = game.player.x;
	y = game.player.y;
	delta_x = game.dda.x2 - game.player.x;
	delta_y = game.dda.y2 - game.player.y;
	if (fabs(delta_x) > fabs(delta_y))
		length = fabs(delta_x);
	else
		length = fabs(delta_y);
	x_inc = delta_x / length;
	y_inc = delta_y / length;
	while (length-- > 0)
	{
		my_mlx_pixel_put(&game.img, x, y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	dda_wall(t_cub3d game,int color)
{
	double	delta_x;
	double	delta_y;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	double	length;

	x = game.dda.x1;
	y = game.dda.y1;
	delta_x = game.dda.x2 - x;
	delta_y = game.dda.y2 - y;
	if (fabs(delta_x) > fabs(delta_y))
		length = fabs(delta_x);
	else
		length = fabs(delta_y);
	x_inc = delta_x / length;
	y_inc = delta_y / length;
	while (length-- > 0)
	{
		my_mlx_pixel_put(&game.img, x, y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_line(t_cub3d *game, int color)
{
	game->dda.x2 = cos(game->player.rotation_angle) * 20 + game->player.x;
	game->dda.y2 = sin(game->player.rotation_angle) * 20 + game->player.y;
	dda(*game, color);
}

void	draw_player(t_cub3d game)
{
	int		y;
	int		x;
	int		x_player;
	int		y_player;
	
	y = 0;
	y_player = game.player.y - game.info.tile_size / 8;
	x_player = game.player.x - game.info.tile_size / 8;
	while (y < game.info.tile_size / 4)
	{
		x = 0;
		while (x < game.info.tile_size / 4)
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

	y = 0;
	while (y < game.info.tile_size)
	{
		x = 0;
		while (x < game.info.tile_size)
		{
			if (x_pixel + x < game.width && y_pixel + y < game.height)
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

	game.info.y = 0;
	game.info.x = 0;
	y_pixel = 0;
	while (game.pars.map[game.info.y])
	{
		game.info.x = 0;
		x_pixel = 0;
		while (game.pars.map[game.info.y][game.info.x])
		{
			if (game.pars.map[game.info.y][game.info.x] == '1')
				put_square(game, x_pixel, y_pixel, WHITE);
			else if (game.pars.map[game.info.y][game.info.x] == '0' ||
				game.pars.map[game.info.y][game.info.x] == 'N' || game.pars.map[game.info.y][game.info.x] == 'S' ||
				game.pars.map[game.info.y][game.info.x] == 'E' || game.pars.map[game.info.y][game.info.x] == 'W')
					put_square(game, x_pixel, y_pixel, BLACK);
			x_pixel += game.info.tile_size;
			game.info.x++;
		}
		y_pixel += game.info.tile_size;
		game.info.y++;
	}
}