/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:59:34 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/07 10:38:18 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	close_win(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	exit(0);
	return (0);
}

int	key_release(int keycode, t_cub3d *game)
{
	if (keycode == 13)
		game->player.is_up = 0;
	else if (keycode == 1)
		game->player.is_down = 0;
	else if (keycode == 2)
		game->player.is_right = 0;
	else if (keycode == 0)
		game->player.is_left = 0;
	else if (keycode == 124)
		game->player.is_turn_right = 0;
	else if (keycode == 123)
		game->player.is_turn_left = 0;
	return (0);
}

int	key_press(int keycode, t_cub3d *game)
{
	if (keycode == 13)
		game->player.is_up = 1;
	else if (keycode == 1)
		game->player.is_down = 1;
	else if (keycode == 2)
		game->player.is_right = 1;
	else if (keycode == 0)
		game->player.is_left = 1;
	else if (keycode == 124)
		game->player.is_turn_right = 1;
	else if (keycode == 123)
		game->player.is_turn_left = 1;
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		exit(0);
	}
	return (0);
}
