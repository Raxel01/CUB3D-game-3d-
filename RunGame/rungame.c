/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rungame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:06 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 21:06:40 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	init_struct(t_cub3d *game ,t_gamedata pars)
{
	game->height = 720;
	game->width = 1280;
	game->info.tile_size = 32;
	game->info.tex_size = game->info.tile_size;
	game->pars = pars;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		print_error("Error\nmlx_init failed\n");
		return (1);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr,
		game->width, game->height, "Cub3d");
	if (!game->win_ptr)
	{
		print_error("Error\nmlx_new_window failed\n");
		return (1);
	}
	init_player(game);
	init_rays(game);
	init_floor_ciel(game);
	if (init_textures(game))
		return (1);
	return (0);
}

void	run_game(t_gamedata pars)
{
	t_cub3d	game;
	
	if (init_struct(&game, pars))
		return ;
	start(&game);
	mlx_loop_hook(game.mlx_ptr, update, &game);
	mlx_hook(game.win_ptr, 2, 0, key_press, &game.mlx_ptr);
	mlx_hook(game.win_ptr, 3, 0, key_release, &game.mlx_ptr);
	mlx_hook(game.win_ptr, 17, 0, close_win, &game.mlx_ptr);
	mlx_loop(game.mlx_ptr);
}