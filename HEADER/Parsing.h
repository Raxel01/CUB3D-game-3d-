/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 02:55:14 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/08 15:18:37 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9
# endif

# define HEIGHT 720
# define WIDTH 1280

enum					e_path
{
	NORD,
	SOUTH,
	WEST,
	EAST,
};

enum					e_floorciel
{
	FLOOR,
	CIEL,
};

typedef struct rgb
{
	long				*rgb;
	enum e_floorciel	type;
	size_t				member;
	struct rgb			*next;
}						t_rgb;

typedef struct texture
{
	char				*path;
	enum e_path			type;
	size_t				size;
	struct texture		*next;
}						t_textures;

typedef struct data
{
	t_textures			*texture;
	char				**map;
	t_rgb				*color;
	int					onlyplayers;
	int					fd;
}						t_gamedata;

typedef struct trim
{
	int					start_trim;
	int					end_trim;
	int					trim_len;
	char				*trimmed;
	int					i;
}						t_trim;

typedef struct variable
{
	int					i;
	int					flg;
	char				*epured_string;
	char				*begin;
}						t_var;

typedef struct pos
{
	int					player_x;
	int					player_y;
	int					tall_line;
	int					countspace;
	int					height;
	char				**clonedmap;
}						t_playerinfo;

typedef struct split
{
	int					i;
	char				**str;
	char				*tmp;
	int					words;
	int					len;
}						t_split;

/*
	@- CHECK DUP DIRECTION
*/
typedef struct dir
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}					t_direction;

/*
	@- error phase :
*/
void					display_error(char *error);
void					error(char *error);
void					allocation_error(void);
void					extension_error(void);
void					game_usage(void);

/*
	@-General function:
*/
int						getend(char *data);
int						getstart(char *data);
long					ft_atoi(const char *str);
char					*ft_strtrim(char *to_trim);
char					*ft_strrchr(char *str, int c);
int						ft_strcmp(char *s1, char *s2);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strrchr(char *str, int c);
int						cmp_textures(char *s1, char *s2);
char					*ft_strndup(char *to_dup, int len);
int						skipcontent(char *line, int i, char c);

/*
	@-Getline function:
*/
size_t					ft_strlen(char *s);
int						ft_strchr(char *s);
char					*ft_strdup(char *s);
char					*get_next_line(int fd);
char					*get_next_line(int fd);
char					*to_stocked(char *rest);
char					*extract_line(char *buffer);
char					*ft_strjoin(char *s1, char *s2);
char					*read_untilnl(char *joined, int fd);
char					*ft_substr(char *s, unsigned int start, size_t len);

/*
	@-extension checker:
*/
void					extensionvalidity(char *filename);

/*
	@-Epur line (clean line):
*/
void					get_new_string(char *commande, t_var var);
void					data_init(t_var *vars, char *commande);
int						word_epur_helper(char *commande);
int						epur_len_helper(char *commande);
char					*epur_string(char *commande);
/*
	@-textures build list :
*/
t_textures				*build_member(char *t_path, enum e_path direct);
void					addmember(t_textures **head, t_textures *newmember);

/*
	@-color[r,g,b] buildlist :
*/
t_rgb					*creatnode(long *purergb, enum e_floorciel it_type);
void					linknodes(t_rgb **head, t_rgb *newelem);
/*
	@-SPLIT : FUNCTION
*/
char					**ft_split(char *s, char c, int color);
size_t					ft_strlcpy(char *dst, char *src, size_t size);

/*
	@-[Claim: Memory]
*/
void					throwtextures(char *line, t_gamedata *data);
void					claimgamedata(t_gamedata *data);
void					free_textures(t_textures **texture);
char					**freearray(char **array);
void					free_color(t_rgb **color);
/*
	@-[TEXTURE: IMPORTATION]
*/
int						validline(char *line);
int						getspaces(char *line);
void					importtextures(t_gamedata *data);
void					required_textures(t_gamedata *data);
void					textureaccessiblity(t_gamedata *data);
void					west_link(t_gamedata *data, char *line);
void					nord_link(t_gamedata *data, char *line);
void					east_link(t_gamedata *data, char *line);
void					south_link(t_gamedata *data, char *line);
void					recognize_textures(t_gamedata *data, char *line);
/*
	@-[COLOR: IMPORTATION]
*/
long					*verifygrammar(char *line, int index, t_gamedata *data);
long					*final_state(char **rgb, char *line, t_gamedata *data);
long					*checkrange(char **rgb, char *line, t_gamedata *data);
long					*rgb_status(char **rgb, char *line, t_gamedata *data);
void					recognize_color(t_gamedata *data, char *line);
void					ceilingcolor(t_gamedata *data, char *line);
void					floorcolor(t_gamedata *data, char *line);
void					west_link(t_gamedata *data, char *line);
void					requiredcolor(t_gamedata *data);
int						input_state(char *str);

/*
	@-Required elem checker [4 : textures | 2 : colors]
*/
void					requiredelem(t_gamedata *data);
void					init_dir(t_direction *dir);
int						only_elem(t_direction dir);
void					elemnt_diff(t_gamedata *data, t_direction dir);

/*
	@-[Border Analyser]
*/
int						getheight(char **map);
int						lastline(t_gamedata *data);
int						firstline(t_gamedata *data);
void					handleborder(t_gamedata *data);

/*
	@-[Border Begin]
*/
int						firstun(char *map);
void					handlstart(t_gamedata *data);
void					verifybeginline(char *line, t_gamedata *data);
void					upchecker(t_gamedata *data, int i, int firstone);
void					updown_checker(t_gamedata *data, int i, int firstone);
/*
	@-[Border End]
*/
int						indexof_lastelem(char *line);
void					handlmax(t_gamedata *data);
void					verifyendline(char *line, t_gamedata *data);
int						invalidzero(int column, t_gamedata *data, int line);
/*
	@-[elemmap Analyser]
*/
int						diff(char c);
int						playersign(char c);
void					onlyplayer(t_gamedata *data);
void					mapanalyser(t_gamedata *data);
void					elementanalyser(t_gamedata *data);
/*
	@-[Map extraction]
*/
char					*findmap(int fd);
void					extractmap(t_gamedata *data);
void					mapstate(char *map, t_gamedata *data);
/*
	@-[Valid acces]
*/
void					init_pos(t_playerinfo *pos);
char					*reallocer(char *line, int size);
void					_norequiredacces(t_gamedata *data);
char					*fillcopy(char *dest, char *src, int size);
void					player_acces(t_gamedata *data, t_playerinfo *pos);
void					find_fill(t_gamedata *data, t_playerinfo *pos);
void					clone_mapgame(t_gamedata *data, t_playerinfo *pos);
void					check_recursivly(t_gamedata *data, t_playerinfo *pos,
							int y, int x);

#endif