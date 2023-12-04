/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:37:41 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/03 13:51:11 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./HEADER/Parsing.h"
#include "./HEADER/game.h"

// const char	*path_type[] = {"NORD", "SOUTH", "WEST", "EAST"};
// const char	*color_type[] = {"FLOOR", "CIEL"};

void	extensionvalidity(char *filename)
{
	char	*find_ext;
	int		check;

	find_ext = ft_strrchr(filename, '.');
	check = ft_strcmp(find_ext, ".cub");
	if (check != 0)
		extension_error();
}

// void	print_textures(t_textures **begin)
// {
// 	t_textures	*cursur;
// 	if (!(*begin))
//     {
//         write(1, "EMPTY\n", 6);
// 		return ;
//     }
//     cursur = (*begin);
// 	printf("***********************************************************\n");
// 	printf("*       PATH                    |           PATHTYPE      *\n");
// 	printf("***********************************************************\n");
// 	while (cursur)
// 	{
// 		printf("*%-20s\t|\t%-10s\t  *\n", cursur->path,
// 			path_type[cursur->type]);
// 		printf("***********************************************************\n");
// 		cursur = cursur->next;
// 	}
// }

void	parsing(char **av, t_gamedata *data)
{
	importtextures(data);
	required_textures(data);
	requiredcolor(data);
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

// void    leaks()
// {
//     system("leaks cub");
// }

// void    print_color(t_rgb **begin)
// {
//     t_rgb   *cursur;
//     int     i;
//     i = 0;
// 	if (!(*begin))
//     {
//         write(1, "EMPTY\n", 6);
// 		return ;
//     }
//     cursur = (*begin);
// 	printf("*********************************\n");
// 	printf("*       colors     |   TYPE     *\n");
// 	printf("*********************************\n");
// 	while (cursur)
// 	{
//         printf("r: %lu,g: %lu, b: %lu | %s\t*\n", 
//             cursur->rgb[0], cursur->rgb[1], cursur->rgb[2],
	// color_type[cursur->type]);
// 		printf("*********************************\n");
// 		cursur = cursur->next;
// 	}
// }

int	main(int ac, char **av)
{
	int			fd;
	t_gamedata	data;

	fd = 0;
	initial_check(&fd, ac, av);
	init_game(fd, &data);
	parsing(av, &data);
	run_game(data);
	claimgamedata(&data);
	return (0);
}
