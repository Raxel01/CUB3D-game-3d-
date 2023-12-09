/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rungame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:06 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/08 15:40:41 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	init_struct(t_cub3d *game, t_gamedata pars)
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
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
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

int	handle_mouse(int x, int y, t_cub3d *game)
{
	static int	old_x = WIDTH / 2;

	(void)y;
	if (x < 0 || x > WIDTH)
	{
		mlx_mouse_move(game->win_ptr, WIDTH / 2, HEIGHT / 2);
		return (0);
	}
	if (x > old_x)
		turn_right(game);
	if (x < old_x)
		turn_left(game);
	old_x = x;
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
	mlx_hook(game.win_ptr, 6, 0, handle_mouse, &game);
	mlx_hook(game.win_ptr, 17, 0, close_win, &game.mlx_ptr);
	mlx_loop(game.mlx_ptr);
}
