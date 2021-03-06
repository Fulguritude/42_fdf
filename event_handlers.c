/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 03:33:15 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/16 20:54:28 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		show_cam_pos_info(t_control *ctrl)
{
	char *str;

	str = NULL;
	ft_asprintf(&str, "zoom: %.4f", ctrl->cam.polar_pos[0]);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr,
		HALF_DRENWIN_WIDTH + 20, HALF_DRENWIN_HEIGHT + 20, WHITE, str);
	free(str);
	ft_asprintf(&str, "lon: %.4f", ctrl->cam.polar_pos[1]);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr,
		HALF_DRENWIN_WIDTH + 20, HALF_DRENWIN_HEIGHT + 40, WHITE, str);
	free(str);
	ft_asprintf(&str, "lat: %.4f", ctrl->cam.polar_pos[2]);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr,
		HALF_DRENWIN_WIDTH + 20, HALF_DRENWIN_HEIGHT + 60, WHITE, str);
	free(str);
}

/*
** "Key hook"
*/

int		handle_key(int key, void *param)
{
	t_control	*ctrl;

	ctrl = (t_control *)param;
	if (key == XK_KP_Space || key == XK_KP_LCtrl)
		key == XK_KP_Space ? toggle_proj(ctrl) : toggle_debug(ctrl);
	else if (key == XK_KP_Left)
		ctrl->cam.polar_pos[1] -= 0.2;
	else if (key == XK_KP_Right)
		ctrl->cam.polar_pos[1] += 0.2;
	else if (key == XK_KP_Down && ctrl->cam.polar_pos[2] - 0.1 > 0)
		ctrl->cam.polar_pos[2] -= 0.1;
	else if (key == XK_KP_Up && ctrl->cam.polar_pos[2] + 0.1 < PI)
		ctrl->cam.polar_pos[2] += 0.1;
	else if (key == XK_KP_PageDown)
		ctrl->cam.polar_pos[0] *= 1.1;
	else if (key == XK_KP_PageUp)
		ctrl->cam.polar_pos[0] *= 0.9;
	else if (key == XK_KP_Esc)
		exit_error("Software closing.\n", 0);
	vec3_polar_to_cartesian(ctrl->cam.world_pos, ctrl->cam.polar_pos);
	vec3_add(ctrl->cam.world_pos, ctrl->cam.world_pos, ctrl->cam.anchor);
	ctrl->cam = init_cam(ctrl->cam.polar_pos);
	handle_redraw(param);
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
	t_gridpoint			tmp;

	++click_nb;
	ctrl = (t_control*)param;
	if (button == L_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, BLUE);
	else if (button == R_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, GREEN);
	if (click_nb == 1)
	{
		tmp.x = x + HALF_DRENWIN_WIDTH;
		tmp.y = y + HALF_DRENWIN_HEIGHT;
		bresenham(ctrl, last_click_coord, tmp);
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

static void	handle_redraw_helper(t_control *ctrl)
{
	t_gridpoint 	vtx1_pixmap_pos;
	t_gridpoint 	vtx2_pixmap_pos;
	int				i;

	i = -1;
	while (++i < ctrl->fdf.edge_lst_len)
	{
		vtx1_pixmap_pos = ctrl->fdf.edge_lst[i].vtx_from->proj_pos;
		vtx2_pixmap_pos = ctrl->fdf.edge_lst[i].vtx_to->proj_pos;
		vtx1_pixmap_pos.x += REN_WIDTH / 2;
		vtx1_pixmap_pos.y += REN_HEIGHT / 2;
		vtx2_pixmap_pos.x += REN_WIDTH / 2;
		vtx2_pixmap_pos.y += REN_HEIGHT / 2;
		if (point_in_bounds(vtx1_pixmap_pos.x, vtx1_pixmap_pos.y)
				&& point_in_bounds(vtx2_pixmap_pos.x, vtx2_pixmap_pos.y))
			bresenham(ctrl, vtx1_pixmap_pos, vtx2_pixmap_pos);
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr,
							-HALF_DRENWIN_WIDTH, -HALF_DRENWIN_HEIGHT);
	if (ctrl->debug)
		show_cam_pos_info(ctrl);
}

int			handle_redraw(void *param)
{
	t_control	*ctrl;
	t_mat_4b4	w_to_v;
	t_vec_4d	tmp;
	int			i;

	ctrl = (t_control *)param;
	mlximg_clear(ctrl);
	i = -1;
	cam_to_mat(w_to_v, ctrl->cam);
	while (++i < ctrl->fdf.vtx_lst_len)
	{
		vec3_cpy((t_float *)tmp, ctrl->fdf.vtx_lst[i].world_pos);
		tmp[3] = 1.;
		mat44_app_vec((t_float *)tmp, w_to_v, tmp);
//		vec3_sub(ctrl->fdf.vtx_lst[i].view_pos, tmp, (t_float *)w_to_v + 12);
		vec3_scale(ctrl->fdf.vtx_lst[i].view_pos, 10. * ctrl->cam.polar_pos[0],
					ctrl->fdf.vtx_lst[i].view_pos);
		ctrl->fdf.vtx_lst[i].proj_pos =
					ctrl->proj((t_float *)(ctrl->fdf.vtx_lst[i].view_pos));
	}
	handle_redraw_helper(ctrl);
	return (0);
}
