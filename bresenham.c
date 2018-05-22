/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 23:41:50 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/17 23:41:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline int		point_in_bounds(int x, int y)
{
	return (0 <= x && x < REN_WIDTH &&
			0 <= y && y < REN_HEIGHT);
}

static void		draw_vert(t_control *ctrl, t_gridpoint start, int endy)
												//int endx, int endy)
{
	int		inc;
	int		y;

	inc = start.y < endy ? 1 : -1;
	y = start.y + inc;
	if (inc == 1)
		while (y <= endy && point_in_bounds(start.x, y))
		{
			mlximg_setpixel(ctrl, RED, start.x, y);
			y += inc;
		}
	else
		while (y >= endy && point_in_bounds(start.x, y))
		{
			mlximg_setpixel(ctrl, RED, start.x, y);
			y += inc;
		}	
}

static void		draw_horz(t_control *ctrl, t_gridpoint start, int endx)
												//int endx, int endy)
{
	int		inc;
	int		x;

	inc = start.x < endx ? 1 : -1;
	x = start.x + inc;
	if (inc == 1)
		while (x <= endx && point_in_bounds(x, start.y))
		{
			mlximg_setpixel(ctrl, RED, x, start.y);
			x += inc;
		}
	else
		while (x >= endx && point_in_bounds(x, start.y))
		{
			mlximg_setpixel(ctrl, RED, x, start.y);
			x += inc;
		}
}

static void		draw_vertoct(t_control *ctrl, t_gridpoint start, 
							 t_gridpoint end, t_gridpoint d)
{
	int		x;
	int		y;
	int		xinc;
	int		yinc;
	int		acc_er;

	x = start.x;
	y = start.y;
	acc_er = 0;
	xinc = x < end.x ? 1 : -1;
	yinc = y < end.y ? 1 : -1;
	while (y != end.y)
	{
	    acc_er += d.x;
	    if (acc_er >= d.y)
		{
			acc_er -= d.y;
			x += xinc;
		}
		if (!(point_in_bounds(x, y)))
			break ;
		mlximg_setpixel(ctrl, RED, x, y);
		y += yinc;
	}
}

static void		draw_horzoct(t_control *ctrl, t_gridpoint start,
							 t_gridpoint end, t_gridpoint d)
{
	int		x;
	int		y;
	int		xinc;
	int		yinc;
	int		acc_er;

	x = start.x;
	y = start.y;
	acc_er = 0;
	xinc = x < end.x ? 1 : -1;
	yinc = y < end.y ? 1 : -1;
	while (x != end.x)
	{
	    acc_er += d.y;
	    if (acc_er >= d.x)
		{
			acc_er -= d.x;
			y += yinc;
		}
		if (!(point_in_bounds(x, y)))
			break ;
		mlximg_setpixel(ctrl, RED, x, y);
		x += xinc;
	}
}

void			bresenham(t_control *ctrl, t_gridpoint start,
											int endx, int endy)
{
	t_gridpoint		end;
	t_gridpoint		d;

	d.x = ft_abs((endx - start.x) * 2);
	d.y = ft_abs((endy - start.y) * 2);
	end.x = endx;
	end.y = endy;
	mlximg_setpixel(ctrl, RED, start.x, start.y);
	if (d.x == 0 && d.y == 0)
		return ;
	else if (d.x == 0)
		draw_vert(ctrl, start, endy);
	else if (d.y == 0)
		draw_horz(ctrl, start, endx);
	else if (d.x < d.y)
		draw_vertoct(ctrl, start, end, d);
	else
		draw_horzoct(ctrl, start, end, d);
}
