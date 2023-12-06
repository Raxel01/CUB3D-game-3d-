/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:03:52 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/06 09:43:10 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADER/game.h"

int	init_textures(t_cub3d *game)
{
	int	i;
	t_textures	*tmp;
	
	i = 0;
	game->texture = malloc(sizeof(t_texture) * 4);
	tmp = game->pars.texture;
	while (tmp && i < 4)
	{
		game->texture[i].height = 0;
		game->texture[i].width = 0;
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr,\
			tmp->path, &game->texture[i].width, &game->texture[i].height);
		if (!game->texture[i].img)
		{
			print_error("Error\nmlx_xpm_file_to_image failed\n");
			exit(1);
		}
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,\
			&game->texture[i].bits_per_pixel, &game->texture[i].line_length,\
				&game->texture[i].endian);
		if (!game->texture[i].addr)
		{
			print_error("Error\nmlx_get_data_addr failed\n");
			exit(1);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}
