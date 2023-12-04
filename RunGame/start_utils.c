/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:41:38 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/03 14:11:16 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_maplen(t_cub3d *game)
{
	int y;
	int x;

	y = 0;
	x = 0;
	game->map_info.len_x = 0;
	game->map_info.len_y = 0;
	while (game->pars.map[y])
	{
		x = 0;
		while (game->pars.map[y][x])
			x++;
		if (x > game->map_info.len_x)
			game->map_info.len_x = x;
		y++;
	}
	game->map_info.len_y = y;
}