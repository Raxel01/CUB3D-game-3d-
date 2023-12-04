/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:32:56 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/30 14:47:46 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	move_up(t_cub3d *game)
{
	game->player.back_y = game->player.y + sin(game->player.rotation_angle) * game->player.walk_speed;
	game->player.back_x = game->player.x + cos(game->player.rotation_angle) * game->player.walk_speed;
	if (check_wall_collision(*game))
	{
		game->player.y = game->player.back_y;
		game->player.x = game->player.back_x;
	}
	// puts("up");
}

void	move_down(t_cub3d *game)
{
	game->player.back_y = game->player.y - sin(game->player.rotation_angle) * game->player.walk_speed;
	game->player.back_x = game->player.x - cos(game->player.rotation_angle) * game->player.walk_speed;
	if (check_wall_collision(*game))
	{
		game->player.y = game->player.back_y;
		game->player.x = game->player.back_x;
	}
	// puts("down");
}

void	move_right(t_cub3d *game)
{
	game->player.back_y = game->player.y + sin(game->player.rotation_angle + M_PI_2) * game->player.walk_speed;
	game->player.back_x = game->player.x + cos(game->player.rotation_angle + M_PI_2) * game->player.walk_speed;
	if (check_wall_collision(*game))
	{
		game->player.y = game->player.back_y;
		game->player.x = game->player.back_x;
	}
	// puts("right");
}

void	move_left(t_cub3d *game)
{
	game->player.back_x = game->player.x + cos(game->player.rotation_angle - M_PI_2) * game->player.walk_speed;
	game->player.back_y = game->player.y + sin(game->player.rotation_angle - M_PI_2) * game->player.walk_speed;
	if (check_wall_collision(*game))
	{
		game->player.y = game->player.back_y;
		game->player.x = game->player.back_x;
	}
	// puts("left");
}
