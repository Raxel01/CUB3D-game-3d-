/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 02:55:14 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/26 21:32:20 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 9
#endif

enum					e_path
{
    NORD,
    SOUTH,
    WEST,
    EAST,
};

enum    e_floorciel
{
    FLOOR,
    CIEL,
};

typedef struct rgb
{
    long *rgb;
    enum e_floorciel type;
    size_t member;
    struct rgb *next;
}   t_rgb;

typedef struct texture
{
    char            *path;
    enum e_path     type;
    size_t          size;
    struct texture  *next;
}   t_textures;

typedef struct data
{
    t_textures *texture;
    char **map;
    t_rgb   *color;
    int onlyplayers;
}   t_gamedata;

typedef struct trim
{
    int     start_trim;
    int     end_trim;
    int     trim_len;
    char    *trimmed;
    int     i;
}   t_trim;

typedef struct variable
{
	int					i;
	int					flg;
	char				*epured_string;
	char				*begin;
}						t_var;

typedef struct split
{
    int		i;
	char	**str;
	char	*tmp;
	int		words;
	int		len;
}   t_split;
/*
    @- error phase :
*/
void    display_error(char *error);
void    error(char *error);
void    allocation_error();
void    extension_error();
void    game_usage();

/*
    @-General function:
*/
int     getend(char *data);
int     getstart(char *data);
long    ft_atoi(const char *str);
char    *ft_strtrim(char *to_trim);
char	*ft_strrchr(char *str, int c);
int     ft_strcmp(char *s1, char *s2);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strrchr(char *str, int c);
int     cmp_textures(char *s1, char *s2);
char	*ft_strndup(char *to_dup, int len);
int     skipcontent(char *line, int i, char c);

/*
    @-Getline function:
*/
size_t	ft_strlen(char *s); 
int		ft_strchr(char *s);
char	*ft_strdup(char *s);
char	*get_next_line(int fd);
char	*get_next_line(int fd);
char	*to_stocked(char *rest);
char	*extract_line(char *buffer);
char	*ft_strjoin(char *s1, char *s2);
char	*read_untilnl(char *joined, int fd);
char	*ft_substr(char *s, unsigned int start, size_t len);

/*
    @-extension checker:
*/
void    extensionvalidity(char *filename);

/*
    @-Epur line (clean line):
*/
void	get_new_string(char *commande, t_var var);
void	data_init(t_var *vars, char *commande);
int     word_epur_helper(char *commande);
int     epur_len_helper(char *commande);
char	*epur_string(char *commande);
/*
    @-textures build list :
*/
t_textures  *build_member(char *t_path, enum e_path direct);
void        addmember(t_textures **head, t_textures *newmember);

/*
    @-color[r,g,b] buildlist :
*/
t_rgb   *creatnode(long *purergb, enum e_floorciel it_type);
void    linknodes(t_rgb **head, t_rgb *newelem);
/*
    @-SPLIT : FUNCTION
*/
char    **ft_split(char *s, char c, int color);
size_t	ft_strlcpy(char *dst, char *src, size_t size);

/*
    @-[Claim: Memory]
*/
void    throwtextures(int fd, char *line, t_gamedata *data);
void    claimgamedata(int fd, t_gamedata *data);
void	free_textures(t_textures **texture);
char    **freearray(char **array);
void    free_color(t_rgb **color);
/*
    @-[TEXTURE: IMPORTATION]
*/
int     validline(char *line);
int     getspaces(char *line);
void    importtextures(int fd, t_gamedata *data);
void    required_textures(int fd, t_gamedata *data);
void    textureaccessiblity(int fd, t_gamedata *data);
void    west_link(int fd, t_gamedata *data, char *line);
void    nord_link(int fd, t_gamedata *data, char *line);
void    east_link(int fd, t_gamedata *data, char *line);
void    south_link(int fd, t_gamedata *data, char *line);
void    recognize_textures(int fd, t_gamedata *data, char *line);
/*
    @-[COLOR: IMPORTATION]
*/
long    *verifygrammar(int fd, char *line, int index, t_gamedata *data);
long   *final_state(char **rgb, int fd, char *line, t_gamedata *data);
long	*checkrange(char **rgb, int fd, char *line, t_gamedata *data);
long    *rgb_status(char **rgb, int fd, char *line, t_gamedata *data);
void    recognize_color(int fd, t_gamedata *data, char *line);
void    ceilingcolor(int fd, t_gamedata *data, char *line);
void    floorcolor(int fd, t_gamedata *data, char *line);
void    west_link(int fd, t_gamedata *data, char *line);
void    requiredcolor(int fd, t_gamedata *data);
int     input_state(char *str);

#endif