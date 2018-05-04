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
# include "minilibx/mlx.h"


//TODO remove
# include <stdio.h>

//for keypad int codes /usr/include/X11/keysymdef.h
# define XK_KP_Space                      0xff80
# define XK_KP_Tab                        0xff89
# define XK_KP_Enter                      0xff8d
# define XK_KP_Left                       0xff96
# define XK_KP_Up                         0xff97
# define XK_KP_Right                      0xff98
# define XK_KP_Down                       0xff99

# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF

# define L_CLICK		0x1
# define R_CLICK		0x3
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5



typedef	unsigned char	t_u8;
typedef	unsigned short	t_u16;
typedef	unsigned int	t_u32;
typedef	unsigned long	t_u64;
typedef char			t_s8;
typedef short			t_s16;
typedef int				t_s32;
typedef	long			t_s64;
typedef float			t_f32;
typedef double			t_f64;


typedef struct	s_control
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_control;

typedef struct	s_color
{
	t_u8	red;
	t_u8	green;
	t_u8	blue;
	t_u32	color;
}				t_color;

typedef struct	s_quat
{
	t_u64	r;
	t_u64	x;
	t_u64	y;
	t_u64	z;
}				t_quat;

#endif
