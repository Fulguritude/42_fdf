/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 03:33:15 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/18 03:33:26 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** "Key hook"
*/

int		handle_key(int key, void *param)
{
	printf("key: %d, %p\n", key, param);
	return (0);
}

/*
** "Mouse hook"
*/

int		handle_mouse(int button, int x, int y, void *param)
{
	t_control			*ctrl;
	static int			click_nb = -1;
	static t_gridpoint	last_click_coord;

	++click_nb;
	ctrl = (t_control*)param;
	printf("mouse: %d, (%d, %d), %p\n", button, x, y, param);
	if (button == L_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, RED);
	else if (button == R_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, BLUE);
	if (click_nb == 1)
	{
		bresenham(ctrl, last_click_coord,
					x + HALF_DRENWIN_WIDTH, y + HALF_DRENWIN_HEIGHT);
		click_nb = -1;
	}
	last_click_coord.x = x + HALF_DRENWIN_WIDTH;
	last_click_coord.y = y + HALF_DRENWIN_WIDTH;
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr,
							-HALF_DRENWIN_WIDTH, -HALF_DRENWIN_HEIGHT);
	return (0);
}

/*
** "Expose hook"
*/

int		handle_redraw(void *param)
{
	printf("redraw: %p\n", param);
	return (0);
}

