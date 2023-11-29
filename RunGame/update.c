/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:29:09 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/29 20:46:14 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	draw_update(t_cub3d game)
{
	// mlx_clear_window(game.mlx_ptr, game.win_ptr);
	// mlx_destroy_image(game.mlx_ptr, game.img.img);
	game.img.img = mlx_new_image(game.mlx_ptr, game.width, game.height);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
		&game.img.line_length, &game.img.endian);
	draw_map(game);
	draw_player(game);
	draw_line(&game, game.player.x, game.player.y, RED);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.img.img, 0, 0);
}

int	update(t_cub3d *game)
{
	if (game->player.is_up)
		move_up(game);
	if (game->player.is_down)
		move_down(game);
	if (game->player.is_right)
		move_right(game);
	if (game->player.is_left)
		move_left(game);
	// if (game->player.is_turn_right)
		// turn_right(game);
	// if (game->player.is_turn_left)
		// turn_left(game);
	draw_update(*game);
	return (0);
}