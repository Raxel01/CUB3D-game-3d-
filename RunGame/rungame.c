/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rungame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:06 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/29 20:53:24 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"
// #include "../HEADER/Parsing.h"

void	init_struct(t_cub3d *game ,t_gamedata pars)
{
	game->height = 1080;
	game->width = 1920;
	game->pars = pars;
	game->map_info.tile_size = 30;
	game->player.walk_speed = 5;
	game->player.is_up = 0;
	game->player.is_down = 0;
	game->player.is_right = 0;
	game->player.is_left = 0;
	game->player.rotation_angle = 200 * (M_PI / 180);
}

void	run_game(t_gamedata pars)
{
	t_cub3d	game;
	
	init_struct(&game, pars);
	
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr,
		game.width, game.height, "game");
	start(&game);
	mlx_loop_hook(game.mlx_ptr, update, &game);
	mlx_hook(game.win_ptr, 2, 0, key_press, &game.mlx_ptr);
	mlx_hook(game.win_ptr, 3, 0, key_release, &game.mlx_ptr);
	mlx_hook(game.win_ptr, 17, 0, close_win, &game.mlx_ptr);
	mlx_loop(game.mlx_ptr);
}