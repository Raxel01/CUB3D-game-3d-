/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:01:08 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/29 20:20:05 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	start(t_cub3d *game)
{
	game->img.img = mlx_new_image(game->mlx_ptr, game->width, game->height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
		&game->img.line_length, &game->img.endian);
	ft_maplen(game);
	draw_map(*game);
	get_player_position(game);
	draw_player(*game);
	draw_line(game, game->player.x, game->player.y, RED);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
}