/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:37:41 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/07 13:54:25 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./HEADER/Parsing.h"

void	extensionvalidity(char *filename)
{
	char	*find_ext;
	int		check;

	find_ext = ft_strrchr(filename, '.');
	check = ft_strcmp(find_ext, ".cub");
	if (check != 0)
		extension_error();
}

void	parsing(t_gamedata *data)
{
	importtextures(data);
	required_textures(data);
	requiredcolor(data);
	requiredelem(data);
	textureaccessiblity(data);
	extractmap(data);
	mapanalyser(data);
}

void	init_game(int mapfd, t_gamedata *data)
{
	data->texture = NULL;
	data->map = NULL;
	data->color = NULL;
	data->onlyplayers = 0;
	data->fd = mapfd;
}

void	initial_check(int *fd, int ac, char **av)
{
	if (ac != 2)
		display_error("@-PLEASE ENTER ENOUGH ARGUMENTS");
	extensionvalidity(av[1]);
	*fd = open(av[1], O_RDONLY, 0777);
	if (*fd == -1)
		display_error(strerror(errno));
}

int	main(int ac, char **av)
{
	int			fd;
	t_gamedata	data;

	fd = 0;
	initial_check(&fd, ac, av);
	init_game(fd, &data);
	parsing(&data);
	claimgamedata(&data);
	return (0);
}
