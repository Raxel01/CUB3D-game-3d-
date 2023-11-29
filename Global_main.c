/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Global_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:37:41 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/28 18:54:03 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./HEADER/Parsing.h"
#include "./HEADER/game.h"


const char	*path_type[] = {"NORD", "SOUTH", "WEST", "EAST"};
const char	*color_type[] = {"FLOOR", "CIEL"};

void    extensionvalidity(char *filename)
{
	char	*find_ext;
	int		check;

	find_ext = ft_strrchr (filename, '.');
	check = ft_strcmp (find_ext, ".cub");
	if (check != 0)
        extension_error();
}

void	print_textures(t_textures **begin)
{
	t_textures	*cursur;

	if (!(*begin))
    {
        write(1, "EMPTY\n", 6);
		return ;
    }
    cursur = (*begin);
	printf("***********************************************************\n");
	printf("*       PATH                    |           PATHTYPE      *\n");
	printf("***********************************************************\n");
	while (cursur)
	{
		printf("*%-20s\t|\t%-10s\t  *\n", cursur->path,
			path_type[cursur->type]);
		printf("***********************************************************\n");
		cursur = cursur->next;
	}
}

void    mapstate(char *map, int fd, t_gamedata *data)
{
    int elem;
    if (map == NULL)
    {
        claimgamedata(fd, data);
        display_error("\tERROR : No map in File.cub recheck :]");
    }
} 

char    *findmap(int fd)
{
    char *line;
    
    line = get_next_line(fd);
    while(!validline(line))
    {
        free(line);
        line = get_next_line(fd);
    }
    return(line);
}

void    extractmap(int fd, t_gamedata *data)
{
    char *line;
    char *map;

    map = NULL;
    line = findmap(fd);
    while(line)
    {
        if (!validline(line))
        {
            claimgamedata(fd, data);
            free(line);
            free(map);
            display_error("Error :Invalid line in map:");
        }
        else
        {
            map = ft_strjoin(map, line);
            free(line);
        }
        line = get_next_line(fd);
    }
    mapstate(map, fd, data);
    data->map = ft_split(map, '\n', 0);
}

int    diff(char c)
{
    return (c != '1' && c != '0' && c != 'N' \
                && c != ' ' && c != 'W' && c != 'S' && c != 'E');
}

int playersign(char c)
{
    return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

void   elementanalyser(int fd, t_gamedata *data)
{
    int line;
    int column;
    char c;

    line = 0;
    while(data->map[line])
    {
        column = 0;
        while(data->map[line][column])
        {
            c = data->map[line][column];
            if (diff(c))
            {
                write(2, &c, 1);
                claimgamedata(fd, data);
                display_error(" :<<- ERROR : Weird element in The Map");
            }
            if (playersign(c))
                data->onlyplayers++;
            column++;
        }
    line++;
    }
}

void    onlyplayer(int fd, t_gamedata *data)
{
    int to_char;

    to_char = data->onlyplayers + 48;
    if (data->onlyplayers == 0 || data->onlyplayers > 1)
    {
        claimgamedata(fd, data);
        write(2, &to_char, 1);
        display_error(" :<<- Players in map try with 1 player");
    }
}

int    firstline(int fd, t_gamedata *data)
{
    int i;
    char c;
    
    i = 0;
    while(data->map[0][i])
    {
        c = data->map[0][i];
        if (c != '1' && c != ' ')
            return (0);
        i++;
    }
    return (1);
}

int getheight(char **map)
{
    int len;
    
    len = 0;
    while(map[len])
        len++;
    return (len);
}

int    lastline(int fd, t_gamedata *data)
{
    int i;
    char c;
    int height;


    i = 0;
    height = getheight(data->map) - 1;
    while(data->map[height][i])
    {
        c = data->map[height][i];
        if (c != '1' && c != ' ')
            return (0);
        i++;
    }
    return (1);
}

int invalidzero(int column, t_gamedata *data, int line)
{
    return (column > (ft_strlen(data->map[line - 1]) - 1) \
                    || column > (ft_strlen(data->map[line + 1]) - 1));
}

void    verifyendline(char *line, int fd, t_gamedata *data)
{
    int i;

    i = ft_strlen(line) - 1;
    while(line[i] && line[i] == ' ')
        i--;
    if (line[i] != '1')
    {
        write(2, &line[i], 1);
        claimgamedata(fd, data);
        write(2, " : None 1 caractere", 19);
        display_error(" at the end of line");
    }
}

void    handlmax(int fd, t_gamedata *data)
{
    int line;
    int column;
    char hold;

    line = -1;
    while(data->map[++line])
    {
        verifyendline(data->map[line], fd, data);
        column = -1;
        while(data->map[line][++column])
        {
            hold = data->map[line][column];
            if (hold == '0')
            {
                if (invalidzero(column, data, line))
                {
                    claimgamedata(fd, data);
                    display_error("Error : OPEN MAP -> right");
                }
            }
        }
    }
}

int firstun(char *map)
{
    int i;

    i = 0;
    while (map[i])
    {
        if (map[i] == '1')
            return (i);
        i++;
    }
    return (3);
}

void updown_checker(int fd, t_gamedata *data, int i, int firstone)
{
    while (firstone >= 0)
    {
        if ((data->map[i - 1][firstone] == '0' ) || data->map[i + 1][firstone] == '0')
            {
                claimgamedata(fd, data);
                display_error("Error : OPEN MAP <-Left");
            }
        firstone--;
    }
}

void    verifybeginline(char *line, int fd, t_gamedata *data)
{
    int i;

    i = 0;
    while(line[i] && line[i] == ' ')
        i++;
    if(line[i] != '1')
    {
        write(2, &line[i], 1);
        claimgamedata(fd, data);
        display_error(" : None 1 caractere at begin");
    }
}

void    handlstart(int fd, t_gamedata *data)
{
    int i;
    int firstone;

    i = 0;
    while(data->map[i])
    {
        verifybeginline(data->map[i], fd, data);
        if (data->map[i][0] != '1')
        {
            firstone = firstun(data->map[i]);
            updown_checker(fd, data, i, firstone - 1);
        }
        i++;
    }
}

void    handleborder(int fd, t_gamedata *data)
{
    if (!firstline(fd, data) || !lastline(fd, data))
    {
        claimgamedata(fd, data);
        display_error("Error : First/Last Line in map not valid");
    }
    handlstart(fd, data);
    handlmax(fd, data);
    // dupmap = malloc(sizeof(char *) * (getheight(data->map) + 1));
    // int i;
    // i = -1;
    // while(data->map[++i])
    //     dupmap[i] = ft_strdup(data->map[i]);
    // dupmap[i] = NULL;
}

int     getlastone(char *line)
{
    int i;

    i = ft_strlen(line) - 1;
    while(line[i] && line[i] == ' ')
        i--;
    return (i);
}

typedef struct pos
{
    int     player_x;
    int     player_y;
    int     tall_line;
    int     countspace;
    int     height;
    char    **clonedmap;
}   t_playerinfo;

void    init_pos(t_playerinfo *pos)
{
    pos->clonedmap = NULL;
    pos->player_x = 0;
    pos->player_y = 0;
    pos->tall_line = 0;
    pos->countspace = 0;
    pos->height = 0;
}

void    findplayer(t_gamedata *data, t_playerinfo *pos)
{
    int line;
    int column;
    char c;

    line = -1;
    pos->tall_line = ft_strlen(data->map[0]);
    while(data->map[++line])
    {
        if (ft_strlen(data->map[line]) > pos->tall_line)
            pos->tall_line = ft_strlen(data->map[line]) + 1;
        column = -1;
        while(data->map[line][++column])
        {
            c = data->map[line][column];
            if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
                {
                    pos->player_x = column;
                    pos->player_y = line;
                }
            if (c == ' ')
                pos->countspace++;
        }
    }
    pos->height = line + 1;
}

char    *fillcopy(char *dest, char *src, int size)
{
    int     i;

    i = -1;
    while (src[++i])
        dest[i] = src[i];
    while(i < size - 1)
    {
        dest[i] = ' ';
        i++;
    }
    dest[i] = '\0';
    free(src);
    return (dest);
}

char    *reallocer(char *line, int size)
{
    char *new;

    new = malloc(sizeof(char) * size);
    if (!new)
        return (allocation_error(), NULL);
    new = fillcopy(new, line, size);
    return(new);
}

void    طباعةـالشبكة(t_gamedata *data,  t_playerinfo *pos)
{
    int i;
    
    pos->clonedmap = malloc(sizeof(char *) * pos->height);
    i = -1;
    while(data->map[++i])
        pos->clonedmap[i] = reallocer(ft_strdup(data->map[i]), pos->tall_line + 1);
    pos->clonedmap[i] = NULL;
}

void	ft_recursif(t_gamedata *data, t_playerinfo *pos, int y, int x)
{
	if (pos->clonedmap[y][x] == '1' || pos->clonedmap[y][x] == '#')
		return ;
    // if (pos->clonedmap[y][x] == ' ')
    //    flag = 1;
    pos->clonedmap[y][x] = '#';
	// if (flag)
    //     {
    //         claimgamedata(19, data);
    //         display_error("bad acces to space");
    //     }
    ft_recursif(data, pos, y - 1, x);
	ft_recursif(data, pos, y + 1, x);
	ft_recursif(data, pos, y, x - 1);
	ft_recursif(data, pos, y, x + 1);
}

void getinfo(t_gamedata *data, t_playerinfo *pos)
{
    findplayer(data, pos);
    طباعةـالشبكة(data, pos);
    ft_recursif(data, pos, pos->player_y, pos->player_x);
    int i;
    i = 0;
    while(pos->clonedmap[i])
        printf("%s\n", pos->clonedmap[i++]);
}

void   _norequiredacces(int fd, t_gamedata *data)
{
    t_playerinfo pos;

    init_pos(&pos);
    getinfo(data,&pos);
    
}

void    mapanalyser(int fd, t_gamedata *data)
{
    elementanalyser(fd, data);
    onlyplayer(fd, data);
    handleborder(fd, data);
    _norequiredacces(fd, data);
}

void    parsing(int fd, char **av, t_gamedata *data)
{
    extensionvalidity(av[1]);
    importtextures(fd, data);
    required_textures(fd, data);
    requiredcolor(fd, data);
    textureaccessiblity(fd, data);
    extractmap(fd, data);
    mapanalyser(fd, data);
}

void    initial_check(int *fd, int ac, char **av)
{
    if (ac != 2)
        display_error("@-PLEASE ENTER ENOUGH ARGUMENTS");
    *fd = open(av[1], O_RDONLY, 0777);
    if (*fd == -1)
        display_error(strerror(errno));
}

void    init_game(t_gamedata *data)
{
    data->texture = NULL;
    data->map = NULL;
    data->color = NULL;
    data->onlyplayers = 0;
}

void    leaks()
{
    system("leaks cub");
}

void    print_color(t_rgb **begin)
{
    t_rgb	*cursur;
    int i;
    i = 0;

	if (!(*begin))
    {
        write(1, "EMPTY\n", 6);
		return ;
    }
    cursur = (*begin);
	printf("*********************************\n");
	printf("*       colors     |   TYPE     *\n");
	printf("*********************************\n");
	while (cursur)
	{
        printf("r: %lu,g: %lu, b: %lu | %s\t*\n", \
            cursur->rgb[0], cursur->rgb[1], cursur->rgb[2], color_type[cursur->type]);
		printf("*********************************\n");
		cursur = cursur->next;
	}

}

// get the map from the data and put it in the cub3d struct for the game
// recu_data(t_gamedata data)
// {
//     data.cub3d.map_info.map = data.map;
// }


int main (int ac, char **av)
{
    int fd;
    t_gamedata data;

    fd = 0;
    initial_check(&fd, ac, av);
    init_game(&data);
    // recu_data(data);
    parsing(fd, av, &data);
    // claimgamedata(fd,&data);
    // printMap(data.map);
    run_game(data);
    return (0);
}
