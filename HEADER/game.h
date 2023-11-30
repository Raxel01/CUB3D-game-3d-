/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:37:53 by tben-dal          #+#    #+#             */
/*   Updated: 2023/11/30 15:00:47 by tben-dal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "Parsing.h"

// colors
#define BLACK 0x00000000
#define WHITE 0x00FFFFFF
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define PURPLE 0x00FF00FF
#define CYAN 0x0000FFFF


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//for the map info
typedef struct map
{
	char	**map;
	int		tile_size;
	int		len_y;
	int		len_x;
	int		x;
	int		y;
}			t_map;

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
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	
}			t_rays;

typedef struct Player
{
	double	y;
	double	x;
	double	back_y;
	double	back_x;
	double	radius;
	double	rotation_angle;
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
	t_player	player;
	t_map		map_info;
	t_gamedata 	pars;
	t_data		img;
	t_tmp		tmp;
	t_dda		dda;
}			t_cub3d;

// main functions
void	run_game(t_gamedata pars);

//mlx_utils functions
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// mlx_hook functions
int	close_win(t_cub3d *cub3d);

// key functions
int	key_press(int keycode, t_cub3d *game);
int	key_release(int keycode, t_cub3d *game);

// move functions
void	move_up(t_cub3d *game);
void	move_down(t_cub3d *game);
void	move_right(t_cub3d *game);
void	move_left(t_cub3d *game);

// turn functions
void	turn_right(t_cub3d *game);
void	turn_left(t_cub3d *game);

// check functions
int	check_wall_collision(t_cub3d game);

// start functions
void	start(t_cub3d *game);

// init functions
void	init_player(t_cub3d *game);

// start_utils functions
void	ft_maplen(t_cub3d *game);

// update functions
int	update(t_cub3d *game);

// draw functions
void	draw_map(t_cub3d game);
void	draw_player(t_cub3d game);
void	draw_line(t_cub3d *game, int x, int y, int color);
void	dda(t_cub3d game, int color);

// gets functions
void	get_player_position(t_cub3d *game);

#endif