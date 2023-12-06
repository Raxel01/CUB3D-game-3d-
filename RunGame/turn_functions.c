/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:47:36 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/06 23:28:26 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	turn_right(t_cub3d *game)
{
	game->player.rotation_angle += game->player.turn_speed;
}

void	turn_left(t_cub3d *game)
{
	game->player.rotation_angle -= game->player.turn_speed;
}
