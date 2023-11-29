/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:32:56 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/29 20:41:59 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	move_up(t_cub3d *game)
{
	game->player.y -= game->player.walk_speed;
	// puts("up");
}

void	move_down(t_cub3d *game)
{
	game->player.y += game->player.walk_speed;
	// puts("down");
}

void	move_right(t_cub3d *game)
{
	game->player.x += game->player.walk_speed;
	// puts("right");
}

void	move_left(t_cub3d *game)
{
	game->player.x -= game->player.walk_speed;
	// puts("left");
}