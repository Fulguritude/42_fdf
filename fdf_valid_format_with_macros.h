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

# define MAX_LINE_SIZE	4096
# define MAX_LINE_NB	4096

# define WIN_WIDTH				800
# define WIN_HEIGHT				600
# define REN_WIDTH				1000
# define REN_HEIGHT				800
# define HALF_DRENWIN_WIDTH		100
# define HALF_DRENWIN_HEIGHT	100

/*
** for keypad int codes /usr/include/X11/keysymdef.h
*/

# define LINUX		0
# define MACOS		1

# define PLATFORM	LINUX


#if PLATFORM
# define L_CLICK		0x1
# define R_CLICK		0x2
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5

# define KEY_ESC		0x35
# define KEY_SPACE		0x31
# define KEY_LCTRL		0x3B

# define KEY_LEFT		0x7B
# define KEY_RIGHT		0x7C
# define KEY_DOWN		0x7D
# define KEY_UP			0x7E
# define KEY_PAGE_UP	0x74
# define KEY_PAGE_DN	0x79

# define KEY_HOME		0x73
# define KEY_END		0x77
# define KEY_HELP		0x72
# define KEY_DELETE		0x75

# define KEY_NUMPAD_0			0x52
# define KEY_NUMPAD_1			0x53
# define KEY_NUMPAD_2			0x54
# define KEY_NUMPAD_3			0x55
# define KEY_NUMPAD_4			0x56
# define KEY_NUMPAD_5			0x57
# define KEY_NUMPAD_6			0x58
# define KEY_NUMPAD_7			0x59
# define KEY_NUMPAD_8			0x5B
# define KEY_NUMPAD_9			0x5C
# define KEY_NUMPAD_PERIOD		0x41
# define KEY_NUMPAD_ENTER		0x4C
# define KEY_NUMPAD_ADD			0x45
# define KEY_NUMPAD_SUB			0x4E
# define KEY_NUMPAD_MUL			0x43
# define KEY_NUMPAD_DIV			0x4B
# define KEY_NUMPAD_CLEAR		0x47
# define KEY_NUMPAD_EQUALS		0x51


#else
/*
**# define XK_KP_Space					0x0020
**# define XK_KP_Tab						0xff89 //?
**# define XK_KP_Enter					0xff8d
**# define XK_KP_Left						0xff51
**# define XK_KP_Up						0xff52
**# define XK_KP_Right					0xff53
**# define XK_KP_Down						0xff54
**# define XK_KP_PageUp					0xff55
**# define XK_KP_PageDown					0xff56
**# define XK_KP_Esc						0xff1b
**# define XK_KP_LCtrl					0xffe3
*/
# define L_CLICK		0x1
# define M_CLICK		0x2
# define R_CLICK		0x3
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5

# define KEY_ESC		0xFF1B
# define KEY_SPACE		0x0020
# define KEY_LCTRL		0xFFE3

# define KEY_LEFT		0xFF51
# define KEY_UP			0xFF52
# define KEY_RIGHT		0xFF53
# define KEY_DOWN		0xFF54
# define KEY_PAGE_UP	0xFF55
# define KEY_PAGE_DN	0xFF56

# define KEY_HOME		0xFF50
# define KEY_END		0xFF57
# define KEY_INSERT		0xFF63
# define KEY_DELETE		0xFFFF

# define KEY_NUMPAD_0		0xFF9E
# define KEY_NUMPAD_1		0xFF9C
# define KEY_NUMPAD_2		0xFF99
# define KEY_NUMPAD_3		0xFF9B
# define KEY_NUMPAD_4		0xFF96
# define KEY_NUMPAD_5		0xFF9D
# define KEY_NUMPAD_6		0xFF98
# define KEY_NUMPAD_7		0xFF95
# define KEY_NUMPAD_8		0xFF97
# define KEY_NUMPAD_9		0xFF9A
# define KEY_NUMPAD_PERIOD	0xFF9F
# define KEY_NUMPAD_ENTER	0xFF8D
# define KEY_NUMPAD_ADD		0xFFAB
# define KEY_NUMPAD_SUB		0xFFAD
# define KEY_NUMPAD_MUL		0xFFAA
# define KEY_NUMPAD_DIV		0xFFAF

#endif


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

typedef struct	s_color
{
	t_u8			alpha;
	t_u8			red;
	t_u8			green;
	t_u8			blue;
}				t_color;

typedef struct	s_gridpoint
{
	int				x;
	int				y;
	t_color			color;
}				t_gridpoint;

/*
** Model -> World -> View (cam space) -> Projection
*/
typedef struct	s_vertex
{
	t_vec_3d		world_pos;
	t_vec_4d		view_pos;
	t_gridpoint		proj_pos;
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
	t_float			h_scale;
}				t_fdf;

/*
** world_pos; //cartesian coordinate of camera in world
** reltv_pos; //cartesian coordinate of camera with anchor as center
** polar_pos; //zoom/radius, longitude, latitude relative to anchor
** anchor; //origin of polar_pos and reltv_pos
** axis_x; //right
** axis_y; //up
** axis_z; //forward input eye
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
