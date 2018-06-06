/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:35:26 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/18 15:35:29 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

//TODO remove
# ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
# endif

# include <stdio.h>

//# include <X11.h>
# include "minilibx/mlx.h"
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "algebra.h"
# include "libft/hdr/libft_mem.h"
# include "libft/hdr/libft_math.h"
# include "libft/hdr/libft_str.h"

//# define BIG_ENDIAN		1
//# define LIT_ENDIAN		0

# define MAX_LINE_SIZE	4096
# define MAX_LINE_NB	4096

# define WIN_WIDTH				800
# define WIN_HEIGHT				600
# define REN_WIDTH				1000
# define REN_HEIGHT				800
# define HALF_DRENWIN_WIDTH		100
# define HALF_DRENWIN_HEIGHT	100

//for keypad int codes /usr/include/X11/keysymdef.h
//# define XK_KP_Space                      0xff80
# define XK_KP_Space                      0x0020
# define XK_KP_Tab                        0xff89
# define XK_KP_Enter                      0xff8d
/*
# define XK_KP_Left                       0xff96
# define XK_KP_Up                         0xff97
# define XK_KP_Right                      0xff98
# define XK_KP_Down                       0xff99
*/
# define XK_KP_Left						0xff51
# define XK_KP_Up						0xff52
# define XK_KP_Right					0xff53
# define XK_KP_Down						0xff54
# define XK_KP_PageUp					0xff55
# define XK_KP_PageDown					0xff56
# define XK_KP_Esc						0xff1b


# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF

# define L_CLICK		0x1
# define R_CLICK		0x3
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5

typedef struct	s_gridpoint
{
	int				x;
	int				y;
}				t_gridpoint;

typedef struct	s_color
{
	t_u8			alpha;
	t_u8			red;
	t_u8			green;
	t_u8			blue;
}				t_color;

/*
** Model -> World -> View (cam space) -> Projection
*/
typedef struct	s_vertex
{
	t_vec_3d		world_pos;
	t_vec_4d		view_pos;
	t_gridpoint		proj_pos;
	t_color			color;
}				t_vertex;

typedef struct	s_edge
{
	t_vertex		*vtx_from;
	t_vertex		*vtx_to;
}				t_edge;

/*
** _trans is offset so that the map is centered in (0,0,0) 
*/
typedef struct	s_fdf
{
	int				vtx_lst_len;
	int				edge_lst_len;
	t_vertex		*vtx_lst;
	t_edge			*edge_lst;
	int				w_trans;
	int				h_trans;
}				t_fdf;

typedef struct	s_camera
{
	t_vec_3d	world_pos; //cartesian coordinate of camera in world
	t_vec_3d	reltv_pos; //cartesian coordinate of camera with anchor as center
	t_vec_3d	polar_pos; //zoom/radius, longitude, latitude relative to anchor
	t_vec_3d	anchor; //origin of polar_pos and reltv_pos
	t_vec_3d	axis_x; //right
	t_vec_3d	axis_y; //up
	t_vec_3d	axis_z; //forward input eye
}				t_camera;

/*
** bpp Bits per pixel are converted immediately to bytes per pixel,
** bpl bytes per line
** img is bigger than window
*/
typedef struct	s_control
{
	t_fdf			fdf;
	t_camera		cam;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_gridpoint		(*proj)(t_vec_3d const v);
	int				img_bpp;
	int				img_bpl;
	int				img_bytelen;
	int				endian;
	char			*img_data;
}				t_control;

int				handle_key(int key, void *param);
int				handle_mouse(int button, int x, int y, void *param);
int				handle_redraw(void *param);

t_fdf			init_fdf(char *filepath);
t_camera		init_cam(t_vec_3d polar_cam_pos);

void			bresenham(t_control *ctrl, t_gridpoint start, t_gridpoint end);

int				t_color_to_colorint(t_color color);
t_color			new_color(t_u8 alpha, t_u8 red, t_u8 green, t_u8 blue);

int				point_in_bounds(int x, int y);
void			mlximg_setpixel(t_control *ctrl, int color, int x, int y);
void			mlximg_clear(t_control *ctrl);

void			exit_error(char *e_msg, int e_no);


void			cam_to_mat(t_mat_4b4 result, t_camera const cam);
t_gridpoint		orthogonal_proj(t_vec_3d const v);
t_gridpoint		isometric_proj(t_vec_3d const v);
t_gridpoint		topdown_proj(t_vec_3d const v);

#endif
