/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:41:38 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/05 20:12:27 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	if (x < 0 || x >= 1280 || y < 0 || y >= 720)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_maplen(t_cub3d *game)
{
	int y;
	int x;

	y = 0;
	game->info.len_x = 0;
	game->info.len_y = 0;
	while (game->pars.map[y])
	{
		x = 0;
		while (game->pars.map[y][x])
			x++;
		if (x > game->info.len_x)
			game->info.len_x = x;
		y++;
	}
	game->info.len_y = y;
}