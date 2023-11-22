#include "./HEADER/Parsing.h"

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

int getspaces(char *line)
{
    int whitespaces;
    int i;

    i = 0;
    whitespaces = 0;
    while (line[i])
    {
        if (line[i] == ' ' || line[i] == '\t')
            whitespaces++;
        i++;
    }
    return (whitespaces);
}

void	free_textures(t_textures **texture)
{
	t_textures	*cursur;

	while (*texture)
	{
		cursur = *texture;
		(*texture) = (*texture)->next;
		free(cursur->path);
		free(cursur);
	}
    (*texture) = NULL;
}

int	cmp_textures(char *s1, char *s2)
{
	int	i;
	if (s1 == NULL)
		return (404);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void    free_color(t_rgb **color)
{
    t_rgb	*cursur;

    while (*color)
	{
		cursur = *color;
		(*color) = (*color)->next;
		free(cursur->rgb);
		free(cursur);
	}
    (*color) = NULL;

}

void throwtextures(int fd, char *line, t_gamedata *data)
{
    free(line);
    free_textures(&data->texture);
    free_color(&data->color);
    close(fd);
    display_error("|- TEXTURES ERROR -|");
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

void    nord_link(int fd, t_gamedata *data, char *line)
{
    int j;
    char *identifier;

    j = 0;
    while (line[j] && line[j] != ' ' && line[j] != '\t')
        j++;
    identifier = ft_strndup(line, j);
    if (line[j] && line[j] == ' ' || line[j] == '\t')
        j++;
    if (!cmp_textures(identifier, "NO"))
    {
        free(identifier);
        addmember(&data->texture, \
            build_member(ft_strndup(line + j, ft_strlen(line) - j), NORD));
    }
    else
    {
        free(identifier);
        write(2, "NO: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

void    south_link(int fd, t_gamedata *data, char *line)
{
    int j;
    char *identifier;

    j = 0;
    while (line[j] && line[j] != ' ' && line[j] != '\t')
        j++;
    identifier = ft_strndup(line, j);
    if (line[j] && line[j] == ' ' || line[j] == '\t')
        j++;
    if (!cmp_textures(identifier, "SO"))
    {
        free(identifier);
        addmember(&data->texture, \
            build_member(ft_strndup(line + j, ft_strlen(line) - j), SOUTH));
    }
    else
    {
        free(identifier);
        write(2, "SO: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

void    west_link(int fd, t_gamedata *data, char *line)
{
    int j;
    char *identifier;

    j = 0;
    while (line[j] && line[j] != ' ' && line[j] != '\t')
        j++;
    identifier = ft_strndup(line, j);
    if (line[j] && line[j] == ' ' || line[j] == '\t')
        j++;
    if (!cmp_textures(identifier, "WE"))
    {
        free(identifier);
        addmember(&data->texture, \
            build_member(ft_strndup(line + j, ft_strlen(line) - j), WEST));
    }
    else
    {
        free(identifier);
        write(2, "WE: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

void    east_link(int fd, t_gamedata *data, char *line)
{
    int j;
    char *identifier;

    j = 0;
    while (line[j] && line[j] != ' ' && line[j] != '\t')
        j++;
    identifier = ft_strndup(line, j);
    if (line[j] && line[j] == ' ' || line[j] == '\t')
        j++;
    if (!cmp_textures(identifier, "EA"))
    {
        free(identifier);
        addmember(&data->texture, \
            build_member(ft_strndup(line + j, ft_strlen(line) - j), EAST));
    }
    else
    {
        free(identifier);
        write(2, "EA: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

char **freearray(char **array)
{
    int i;

    i = -1;
    while(array[++i])
        free(array[i]);
    free(array);
    array = NULL;
    return (array);
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

long	*checkrange(char **rgb, int fd, char *line, t_gamedata *data)
{
	int	i;
    long *purergb;

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
            throwtextures(fd, line, data);
		}
	}
	return (purergb);
}

long   *final_state(char **rgb, int fd, char *line, t_gamedata *data)
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
            throwtextures(fd, line, data);
        }
		i++;
	}
    return(checkrange(rgb, fd, line, data));
}

long    *rgb_status(char **rgb, int fd, char *line, t_gamedata *data)
{
    int i;
    
    i = -1;
    if (rgb == NULL || rgb[0] == NULL)
    {
        if(rgb)
            free(rgb);
        error("\tCHECK GRAMMAR AND  RETRY : ");
        error("\t   [ID][Space][r,g,b]");
        throwtextures(fd, line, data);
    }
    while(rgb[++i]);
    if (i != 3)
    {
        error("\tMAY you used this syntax : ");
        error("\t::r,g:without entring bleu verify : ");
        error("\t   [ID][Space][r,g,b]");
        rgb = freearray(rgb);
        throwtextures(fd, line, data);
    }
    return(final_state(rgb, fd, line, data));
}

long    *verifygrammar(int fd, char *line, int index, t_gamedata *data)
{
    char **rgb;

    rgb = ft_split(ft_strndup(line + index , \
        ft_strlen(line) - index), ',');
    return(rgb_status(rgb, fd, line, data));
}

void    floorcolor(int fd, t_gamedata *data, char *line)
{
    int     index;
    char    *id;

    index = 0;
    while (line[index] && line[index] != ' ' && line[index] != '\t')
        index++;
    id = ft_strndup(line, index);
    if (line[index] && line[index] == ' ' || line[index] == '\t')
        index++;
    if (!cmp_textures(id, "F"))
    {
        free(id);
        linknodes(&data->color, \
            creatnode(verifygrammar(fd, line, index, data), FLOOR));
    }
    else
    {
        free(id);
        write(2, "F: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

void    ceilingcolor(int fd, t_gamedata *data, char *line)
{
    int     index;
    char    *id;

    index = 0;
    while (line[index] && line[index] != ' ' && line[index] != '\t')
        index++;
    id = ft_strndup(line, index);
    if (line[index] && line[index] == ' ' || line[index] == '\t')
        index++;
    if (!cmp_textures(id, "C"))
    {
        free(id);
        linknodes(&data->color, \
            creatnode(verifygrammar(fd, line, index, data), CIEL));
    }
    else
    {
        free(id);
        write(2, "C: IDENTIFIER ERROR\n", 21);
        throwtextures(fd, line, data);
    }
}

void    recognize_color(int fd, t_gamedata *data, char *line)
{
    if (line[0] == 'F')
        floorcolor(fd, data, line);
    else if (line[0] == 'C')
        ceilingcolor(fd, data, line);
}

/*TEXTURES GRAMMAR : [ID](SPCAE)[PATH]*/
/*COLOR GRAMMAR    :[ID](SPCAE)[R,G,B]*/
void    recognize_textures(int fd, t_gamedata *data, char *line)
{
    int     i;
    int     whitespaces;

    i = 0;
    line = ft_strtrim(line);
    whitespaces = getspaces(line);
    if (whitespaces == 1)
    {
        if (line[i] == 'N')
            nord_link(fd, data, line);
        else if (line[i] == 'S')
            south_link(fd, data, line);
        else if (line[i] == 'W')
            west_link(fd, data, line);
        else if (line[i] == 'E')
            east_link(fd, data, line);
        else
            recognize_color(fd, data, line);
        free(line);
    }
    else
        throwtextures(fd, line, data);
}

int validline(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (1);
        i++;
    }
    return (0);
}

void    importtextures(int fd, t_gamedata *data)
{
    int     i;
    char    *line;

    i = 0;
    line = get_next_line(fd);
    while (line && i < 6)
    {
        if (validline(line))
        {
            recognize_textures(fd, data, line);
            i++;
        }
        else
            free(line);
        if(i == 6)
            break;
        line = get_next_line(fd);
    }
}

void    required_textures(int fd, t_gamedata *data)
{
    if (data->texture)
    {
        if (data->texture->size != 4)
        {
            free_textures(&data->texture);
            close(fd);
            write(2, "Required: 4 textures", 20);
            write(2, "(EA WE SO NO)\n", 14);
            display_error("\tERROR OCCURED : NO ENOUGH TEXTURES");
        }
    }
}

void    requiredcolor(int fd, t_gamedata *data)
{
    if (data->color)
    {
        if (data->color->member != 2)
        {
            free_textures(&data->texture);
            free_color(&data->color);
            close(fd);
            display_error("\tERROR : NO ENOUGH COLOR FOR CIELFLOOR");
        }
    }
}

void        textureaccessiblity(int fd, t_gamedata *data)
{
    t_textures *curs;
    int acces;

    acces = 0;
    curs = data->texture;
    while(curs)
    {
        acces = open(curs->path, O_RDONLY, 0666);
        if (acces == -1)
        {
            error("\tInaccessible Texture");
            free_textures(&data->texture);
            free_color(&data->color);
            close(fd);
            display_error("");
        }
        curs = curs->next;
    } 

}

void    parsing(int fd, char **av, t_gamedata *data)
{
    extensionvalidity(av[1]);
    importtextures(fd, data);
    required_textures(fd, data);
    requiredcolor(fd, data);
    textureaccessiblity(fd, data);
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

void    claimgamedata(t_gamedata *data)
{
    free_color(&data->color);
    free_textures(&data->texture);
}

int main (int ac, char **av)
{
    atexit(leaks);
    int fd;
    t_gamedata data;
    
    fd = 0;
    initial_check(&fd, ac, av);
    init_game(&data);
    parsing(fd, av, &data);
    claimgamedata(&data);
    return (0);
}
