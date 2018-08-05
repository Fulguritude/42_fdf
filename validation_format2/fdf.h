/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:35:26 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/16 21:02:33 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** stdio contains perror
*/
# include <mlx.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include "libft/hdr/libft_mem.h"
# include "libft/hdr/libft_algebra.h"
# include "libft/hdr/libft_str.h"
# include "libft/hdr/get_next_line.h"
# include "libft/hdr/ft_printf.h"
# include "mlx_event_mac.h"

# define MAX_LINE_SIZE	4096
# define MAX_LINE_NB	4096

# define WIN_WIDTH				800
# define WIN_HEIGHT				600
# define REN_WIDTH				1000
# define REN_HEIGHT				800
# define HALF_DRENWIN_WIDTH		100
# define HALF_DRENWIN_HEIGHT	100

# define PROJ_CST1		0.5
# define PROJ_CST1_HLF	0.25
# define PROJ_CST2		0.6
# define PROJ_CST2_HLF	0.3

# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF

# define INIT_H_SCALE	1.

/*
** make a union ?
*/
typedef struct	s_color
{
	t_u8			alpha;
	t_u8			red;
	t_u8			green;
	t_u8			blue;
}				t_color;

/*
** A pixel, with its coordinates and color
*/
typedef struct	s_gridpoint
{
	int				x;
	int				y;
	t_color			color;
}				t_gridpoint;

/*
** Each vertex is a point in our worldspace
** Model -> World -> View (cam space) -> Projection; where each -> is a matrix,
**		the first matrix being the identity.
*/
typedef struct	s_vertex
{
	t_vec_3d		world_pos;
	t_vec_4d		view_pos;
	t_gridpoint		proj_pos;
}				t_vertex;

/*
** A pair of two vertices to draw each "wire"
*/
typedef struct	s_edge
{
	t_vertex		*vtx_from;
	t_vertex		*vtx_to;
}				t_edge;

/*
** vtx_lst_len	: length of the vertex list
** edge_lst_len : length of the edge list
** vtx_lst		: list of all points to plot
** edge_lst		: list of all pairs of points that create a line to plot
** w_trans		: x offset so that the map is centered in (0,0,0) of our wspace
** h_trans		: y offset so that the map is centered in (0,0,0) of our wspace
** h_scale		: parameter that scales the z:x == z:y ratio in our wspace,
**					used to modify height of points before representation.
*/
typedef struct	s_fdf
{
	int				vtx_lst_len;
	int				edge_lst_len;
	t_vertex		*vtx_lst;
	t_edge			*edge_lst;
	int				w_trans;
	int				h_trans;
	t_float			h_scale;
}				t_fdf;

/*
** world_pos		: cartesian coordinate of camera in world
** reltv_pos		: cartesian coordinate of camera with anchor as center
** polar_pos		: zoom/radius, longitude, latitude relative to anchor
** anchor			: origin of polar_pos and reltv_pos
** axis_x			: right vector of cam
** axis_y			: up vector of cam
** axis_z			: "forward" vector of cam,  input eye vector
*/
typedef struct	s_camera
{
	t_vec_3d		world_pos;
	t_vec_3d		reltv_pos;
	t_vec_3d		polar_pos;
	t_vec_3d		anchor;
	t_vec_3d		axis_x;
	t_vec_3d		axis_y;
	t_vec_3d		axis_z;
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
	int				debug;
}				t_control;

/*
** event_handlers.c
*/
int				handle_key(int key, void *param);
int				handle_mouse(int button, int x, int y, void *param);
int				handle_redraw(void *param);

/*
** reader_fdf.c
*/
t_fdf			init_fdf(char *filepath);

/*
** bresenham.c
*/
void			bresenham(t_control *ctrl, t_gridpoint start, t_gridpoint end);

/*
** color.c
*/
int				t_color_to_colorint(t_color color);
t_color			new_color(t_u8 alpha, t_u8 red, t_u8 green, t_u8 blue);

/*
** image_utils.c
*/
int				point_in_bounds(int x, int y);
void			mlximg_setpixel(t_control *ctrl, int color, int x, int y);
void			mlximg_clear(t_control *ctrl);

/*
** camera.c
*/
t_camera		init_cam(t_vec_3d polar_cam_pos);
void			cam_to_mat(t_mat_4b4 result, t_camera const cam);

/*
** main_fdf.c
*/
void			toggle_debug(t_control *ctrl);
void			exit_error(char *e_msg, int e_no);
void			show_debug_info(t_control *ctrl);

/*
** projectors.c
*/
t_gridpoint		orthogonal_proj(t_vec_3d const v);
t_gridpoint		isometric_proj(t_vec_3d const v);
t_gridpoint		topdown_proj(t_vec_3d const v);
void			toggle_proj(t_control *ctrl);

/*
** coordinates.c
*/
void			vec3_polar_to_cartesian(t_vec_3d result, t_vec_3d const src);
void			vec3_cartesian_to_polar(t_vec_3d result, t_vec_3d const src);

#endif
