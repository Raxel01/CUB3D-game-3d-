/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:15:12 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/20 20:18:48 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL)
		return (404);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strrchr(char *str, int c)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen (str);
	if (c == '\0')
		return ((char *)(str + i));
	while (i >= 0)
	{
		if ((char )str[i] == (char)c)
		{
			if (*(str + i - 1))
				return ((char *)(str + i));
		}
		i--;
	}
	return (NULL);
}

// typedef struct map
// {
//     char    **map;
//     int     map_len;
//     char    *line;
// }   t_map;



// int maplen(int fd, t_map *info, char **av)
// {
//     int i;

//     i = 0;
//     info->line = get_next_line(fd);
//     while(info->line && i < 4)
//     {
//         if (ft_strcmp("\n", info->line) != 0)
//         {
//             recognize_textures(info->line);
//             i++;
//         }
//         free (info->line);
//         info->line = get_next_line(fd);
//     }
//     close(fd);
//     exit(1);
//     return (info->map_len);
// }

// void    init_map(t_map *info)
// {
//     info->map_len = 0;
//     info->line = NULL;
//     info->map = NULL;
// }

// char    **extract_map(int fd, char **av)
// {
//     t_map info;
//     int i;

//     init_map(&info);
//     maplen(fd, &info,av);
//     info.map = (char **)malloc(sizeof(char *) * (info.map_len + 1));
//     if (info.map == NULL)
//         return (printf("ALLOC ERROR\n"), NULL);
//     i = 0;
//     info.line = get_next_line(fd);
//     while(info.line)
//     {
//         if (ft_strcmp("\n", info.line)!= 0)
//         {
//             info.map[i] = info.line;
//             i++;
//         }
//         info.line = get_next_line(fd);
//     }
//     info.map[i] = NULL;
//     close(fd);
//     return (info.map);
// }

// int main (int ac, char **av)
// {
//     if (ac == 2)
//     {
//         extensionvalidity(av[1]);
//         char **map = extract_map(fd, av);
//         int k = 0;
//         while (map[k])
//             printf("%s", map[k++]);
//     }
//     else
//         write(1, "NO ENOUGH ARGUMENTS\n", 20);
//     return (0);
// }

// typedef struct info
// {
//     char    **map;
//     char    **textures_path;
//     int     **floar;

//     struct info *next;
// }   t_mapinfo;

/*re_check : PRoTECT AGAINST NULL*/