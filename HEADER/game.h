/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:37:53 by tben-dal          #+#    #+#             */
/*   Updated: 2023/12/07 10:52:59 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "Parsing.h"

// colors
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define PURPLE 0x00FF00FF
# define CYAN 0x0000FFFF
# define GREY 0x00A9A9A9
# define ORANGE 0x00FFA500
# define BROWN 0x00A52A2A
# define PINK 0x00FFC0CB
# define LIME 0x00BFFF00
# define MAGENTA 0x00FF00FF
# define MAROON 0x00800000
# define OLIVE 0x00808000
# define TEAL 0x00008080
# define NAVY 0x00000080
# define SKY 0x0087CEEB
# define SEAGREEN 0x002E8B57
# define FORESTGREEN 0x00228B22
# define GOLD 0x00FFD700
# define FIREBRICK 0x00B22222
# define CRIMSON 0x00DC143C
# define DARKORANGE 0x00FF8C00
# define DARKORCHID 0x009932CC
# define DARKSLATEBLUE 0x00483D8B
# define DARKTURQUOISE 0x0000CED1
# define DEEPPINK 0x00FF1493
# define DEEPSKYBLUE 0x0000BFFF
# define DIMGRAY 0x00696969
# define DODGERBLUE 0x001E90FF
# define GOLDENROD 0x00DAA520
# define GREENYELLOW 0x00ADFF2F
# define HOTPINK 0x00FF69B4
# define INDIANRED 0x00CD5C5C
# define INDIGO 0x004B0082
# define KHAKI 0x00F0E68C
# define LAWNGREEN 0x007CFC00
# define LIGHTCORAL 0x00F08080
# define SKYBLUE 0x0087CEEB

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//for the texture
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	double	offset_x;
	double	offset_y;
}				t_texture;

//for the map info
typedef struct info
{
	char	**map;
	int		tile_size;
	int		tex_size;
	int		floor_color;
	int		ceil_color;
	int		len_y;
	int		len_x;
	int		x;
	int		y;
}			t_info;

typedef struct dda
{
	double	delta_x;
	double	delta_y;
	double	x_inc;
	double	y_inc;
	double	x1;
	double	y1;
	double	x2;
	double	y2;
}			t_dda;

typedef struct rays
{
	double	ray_angle;
	double	hxinter;
	double	hyinter;
	double	vxinter;
	double	vyinter;
	double	hit_d_h;
	double	hit_d_v;
}			t_rays;

typedef struct Player
{
	double	y;
	double	x;
	double	back_y;
	double	back_x;
	double	radius;
	double	rotation_angle;
	double	field_of_view;
	double	turn_direction;
	double	turn_speed;
	double	walk_speed;
	bool	is_up;
	bool	is_down;
	bool	is_left;
	bool	is_right;
	bool	is_turn_left;
	bool	is_turn_right;
}			t_player;

typedef struct cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			height;
	int			width;
	int			num_rays;
	t_player	player;
	t_info		info;
	t_texture	*texture;
	t_gamedata	pars;
	t_data		img;
	t_rays		rays;
	t_dda		dda;
}			t_cub3d;

// main functions
void	run_game(t_gamedata pars);

//mlx_utils functions
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	init_rays(t_cub3d *game);

// mlx_hook functions
int		close_win(t_cub3d *cub3d);

// key functions
int		key_press(int keycode, t_cub3d *game);
int		key_release(int keycode, t_cub3d *game);

// move functions
void	move_up(t_cub3d *game);
void	move_down(t_cub3d *game);
void	move_right(t_cub3d *game);
void	move_left(t_cub3d *game);

// turn functions
void	turn_right(t_cub3d *game);
void	turn_left(t_cub3d *game);

// check functions
int		check_wall_collision(t_cub3d game);

// start functions
void	start(t_cub3d *game);

// init functions
void	init_player(t_cub3d *game);
int		init_textures(t_cub3d *game);
void	init_floor_ciel(t_cub3d *game);

// start_utils functions
void	ft_maplen(t_cub3d *game);
void	print_error(char *str);

// update functions
int		update(t_cub3d *game);

// cast rays functions
void	get_v_i_ray(t_cub3d *game);
void	get_h_i_ray(t_cub3d *game);

// Wall functions
void	dda_wall(t_cub3d game, int color);
void	wall_rendring(t_cub3d *game);
void	h_wall(t_cub3d *game, double distance_proj_plane, int rays_id);
void	v_wall(t_cub3d *game, double distance_proj_plane, int rays_id);
void	put_h_wall(t_cub3d *game, double wall_heightb, int rays_id);
void	put_v_wall(t_cub3d *game, double wall_heightb, int rays_id);
void	tex_render(t_cub3d *game, double wall_heightb, int rays_id, int side);

// gets functions
void	get_player_position(t_cub3d *game);
int		get_color(t_texture texture, int x, int y);

#endif