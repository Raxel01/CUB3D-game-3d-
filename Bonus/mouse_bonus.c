/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:27:35 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/07 12:02:57 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/Parsing.h"

int	handle_mouse(int x, int y, t_cub3d *game)
{
	static int	old_x = WIDTH / 2;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (0);
	mlx_mouse_hide();
	if (x > old_x)
		game->player.rotation_angle += 0.2;
	else if (x < old_x)
		game->player.rotation_angle -= 0.2;
	old_x = x;
	return (0);
}
