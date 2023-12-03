/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbchecker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:11 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/28 15:42:36 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

long	*checkrange(char **rgb, char *line, t_gamedata *data)
{
	int		i;
	long	*purergb;

	i = -1;
	purergb = malloc(sizeof(long) * 3);
	while (rgb[++i])
		purergb[i] = ft_atoi(rgb[i]);
	rgb = freearray(rgb);
	i = -1;
	while (++i < 3)
	{
		if (purergb[i] > 255 || purergb[i] < 0)
		{
			free(purergb);
			error("COLOR : OUT OF RANG");
			throwtextures(line, data);
		}
	}
	return (purergb);
}

int	input_state(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

long	*final_state(char **rgb, char *line, t_gamedata *data)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (!(input_state(rgb[i])))
		{
			error("\tInvalid color Type");
			error("color elem can be just a digit:[0-255],...");
			rgb = freearray(rgb);
			throwtextures(line, data);
		}
		i++;
	}
	return (checkrange(rgb, line, data));
}

long	*rgb_status(char **rgb, char *line, t_gamedata *data)
{
	int	i;

	i = -1;
	if (rgb == NULL || rgb[0] == NULL)
	{
		if (rgb)
			free(rgb);
		error("\tCHECK GRAMMAR AND  RETRY : ");
		error("\t   [ID][Space][r,g,b]");
		throwtextures(line, data);
	}
	while (rgb[++i])
		;
	if (i != 3)
	{
		error("\tMAY you used this syntax : ");
		error("\t::r,g:without entring bleu verify : ");
		error("\t   [ID][Space][r,g,b]");
		rgb = freearray(rgb);
		throwtextures(line, data);
	}
	return (final_state(rgb, line, data));
}

void	requiredcolor(t_gamedata *data)
{
	if (!data->color || data->color->member != 2)
	{
		free_textures(&data->texture);
		free_color(&data->color);
		close(data->fd);
		display_error("\tERROR : NO ENOUGH COLOR FOR CIELFLOOR");
	}
}
