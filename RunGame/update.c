/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:29:09 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 20:57:42 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void draw_floor_cell(t_cub3d game)
{
	int i;
	int j;
	
	i = 0;
	while (i < game.height)
	{
		j = 0;
		while (j < game.width)
		{
			if (i < game.height / 2)
				my_mlx_pixel_put(&game.img, j, i, SKYBLUE);
			else
				my_mlx_pixel_put(&game.img, j, i, DIMGRAY);
			j++;
		}
		i++;
	}
}

void	draw_update(t_cub3d *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img.img);
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	game->img.img = mlx_new_image(game->mlx_ptr, game->width, game->height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
		&game->img.line_length, &game->img.endian);
	draw_floor_cell(*game);
	wall_rendring(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
}

int	update(t_cub3d *game)
{
	if (game->player.is_up == 1)
		move_up(game);
	if (game->player.is_down == 1)
		move_down(game);
	if (game->player.is_right == 1)
		move_right(game);
	if (game->player.is_left == 1)
		move_left(game);
	if (game->player.is_turn_right == 1)
		turn_right(game);
	if (game->player.is_turn_left == 1)
		turn_left(game);
	draw_update(game);
	return (0);
}