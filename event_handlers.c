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
	t_control	*ctrl;

	ctrl = (t_control *)param;
	printf("key: %d, %x, %p;\n", key, key, param);
	if (key == XK_KP_Space)
	{
		printf("toggling proj:\n");
		if (ctrl->proj == &topdown_proj)
			ctrl->proj = orthogonal_proj;
		else if (ctrl->proj == &orthogonal_proj)
			ctrl->proj = isometric_proj;
		else
			ctrl->proj = topdown_proj;
//		return (0);
	}
	else if (key == XK_KP_Left)
	{
		printf("longitutidinal decrease:\n");
		ctrl->cam.polar_pos[1] -= 0.2;
		if (ctrl->cam.polar_pos[1] < 0)
			ctrl->cam.polar_pos[1] += TAU;
	}
	else if (key == XK_KP_Right)
	{
		printf("longitutidinal increase:\n");
		ctrl->cam.polar_pos[1] += 0.2;
		if (ctrl->cam.polar_pos[1] > TAU)
			ctrl->cam.polar_pos[1] -= TAU;
	}
	else if (key == XK_KP_Down)
	{
		printf("latitutidinal decrease:\n");
		if (ctrl->cam.polar_pos[2] - 0.1 > 0)
			ctrl->cam.polar_pos[2] -= 0.1;
	}
	else if (key == XK_KP_Up)
	{
		printf("latitutidinal increase:\n");
		if (ctrl->cam.polar_pos[2] + 0.1 < PI)
			ctrl->cam.polar_pos[2] += 0.1;
	}
	else if (key == XK_KP_PageDown)
	{
		printf("zoom out:\n");
		ctrl->cam.polar_pos[0] *= 1.1;
	}
	else if (key == XK_KP_PageUp)
	{
		printf("zoom in:\n");
		ctrl->cam.polar_pos[0] *= 0.9;
	}
	else if (key == XK_KP_Esc)
		exit_error("Software closing.\n", 0);

	vec3_polar_to_cartesian(ctrl->cam.world_pos, ctrl->cam.polar_pos);
	vec3_add(ctrl->cam.world_pos, ctrl->cam.world_pos, ctrl->cam.anchor);
	ctrl->cam = init_cam(ctrl->cam.polar_pos);
//printf("\tevent cam axis_x : (%f, %f, %f)\n", ctrl->cam.axis_x[0], ctrl->cam.axis_x[1], ctrl->cam.axis_x[2]);
//printf("\tevent cam axis_y : (%f, %f, %f)\n", ctrl->cam.axis_y[0], ctrl->cam.axis_y[1], ctrl->cam.axis_y[2]);
//printf("\tevent cam axis_z : (%f, %f, %f)\n", ctrl->cam.axis_z[0], ctrl->cam.axis_z[1], ctrl->cam.axis_z[2]);
	mlximg_clear(ctrl);
	handle_redraw(param);

//mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string );
char *str = NULL;
asprintf(&str, "zoom: %.4f", ctrl->cam.polar_pos[0]);
mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, HALF_DRENWIN_WIDTH + 20, HALF_DRENWIN_HEIGHT + 20, WHITE, str);
free(str);

asprintf(&str, "lon: %.4f", ctrl->cam.polar_pos[1]);
mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, HALF_DRENWIN_WIDTH + 20, HALF_DRENWIN_HEIGHT + 40, WHITE, str);
free(str);

asprintf(&str, "lat: %.4f", ctrl->cam.polar_pos[2]);
mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, HALF_DRENWIN_WIDTH + 20, HALF_DRENWIN_HEIGHT + 60, WHITE, str);
free(str);
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
	printf("mouse: %d, (%d, %d), %p\n", button, x, y, param);
	if (button == L_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, RED);
	else if (button == R_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, BLUE);
	if (click_nb == 1)
	{
		tmp.x = x + HALF_DRENWIN_WIDTH;
		tmp.y = y + HALF_DRENWIN_HEIGHT;
printf("mouse bresenham\n\t(%d,%d); (%d,%d)\n", last_click_coord.x, last_click_coord.y, tmp.x, tmp.y);
		bresenham(ctrl, last_click_coord, tmp);
		click_nb = -1;
	}
	last_click_coord.x = x + HALF_DRENWIN_WIDTH;
	last_click_coord.y = y + HALF_DRENWIN_WIDTH;
printf("mouse put image\n");
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr,// 0, 0);
							-HALF_DRENWIN_WIDTH, -HALF_DRENWIN_HEIGHT);
	return (0);
}

/*
** "Expose hook"
*/

int		handle_redraw(void *param)
{
	t_control	*ctrl;
	t_mat_4b4	w_to_v;
	t_vec_4d	tmp;
	int			i;

	ctrl = (t_control *)param;
printf("redraw1: %p\n\tpolar pos (%f, %f, %f)\n", param, ctrl->cam.polar_pos[0],  ctrl->cam.polar_pos[1],  ctrl->cam.polar_pos[2]);
	i = -1;
	cam_to_mat(w_to_v, ctrl->cam);
printf("\tcam mat transpose\n\t\t%.3f %.3f %.3f %.3f\n\t\t%.3f %.3f %.3f %.3f\n\t\t%.3f %.3f %.3f %.3f\n\t\t%.3f %.3f %.3f %.3f\n\n", w_to_v[0], w_to_v[1], w_to_v[2], w_to_v[3], w_to_v[4], w_to_v[5], w_to_v[6], w_to_v[7], w_to_v[8], w_to_v[9], w_to_v[10], w_to_v[11], w_to_v[12], w_to_v[13], w_to_v[14], w_to_v[15]);
	while (++i < ctrl->fdf.vtx_lst_len)
	{
		//make one single obj to proj matrix rather than these steps
		vec3_cpy((t_float *)tmp, ctrl->fdf.vtx_lst[i].world_pos);
		tmp[3] = 1.;
if (i == 104) printf("\t(%6.3f, %6.3f, %6.3f, %6.3f)", tmp[0], tmp[1], tmp[2], tmp[3]);
		mat44_app_vec((t_float *)tmp, w_to_v, tmp);
if (i == 104) printf("\t--cam->\t(%6.3f, %6.3f, %6.3f, %6.3f)", tmp[0], tmp[1], tmp[2], tmp[3]);
		vec3_sub(ctrl->fdf.vtx_lst[i].view_pos, tmp, (t_float *)w_to_v + 12);
vec3_cpy(tmp, ctrl->fdf.vtx_lst[i].view_pos);
if (i == 104) printf("\t--sub w_to_v[12:16[->\t(%6.3f, %6.3f, %6.3f, %6.3f)\n", tmp[0], tmp[1], tmp[2], tmp[3]);
vec3_scale(ctrl->fdf.vtx_lst[i].view_pos, 10. * ctrl->cam.polar_pos[0], ctrl->fdf.vtx_lst[i].view_pos);
		ctrl->fdf.vtx_lst[i].proj_pos = ctrl->proj((t_float *)(ctrl->fdf.vtx_lst[i].view_pos));
if (i == 104) printf("\t--proj_pos->\t(%d, %d)\n", ctrl->fdf.vtx_lst[i].proj_pos.x, ctrl->fdf.vtx_lst[i].proj_pos.y);
	}

	t_gridpoint 	vtx1_pixmap_pos;
	t_gridpoint 	vtx2_pixmap_pos;

	i = -1;
printf("redraw2: %p\n", param);
	while (++i < ctrl->fdf.edge_lst_len)
	{
		vtx1_pixmap_pos = ctrl->fdf.edge_lst[i].vtx_from->proj_pos;
		vtx2_pixmap_pos = ctrl->fdf.edge_lst[i].vtx_to->proj_pos;
if (i == 104) printf("\t(%d, %d) ; (%d, %d)\n", vtx1_pixmap_pos.x, vtx1_pixmap_pos.y, vtx2_pixmap_pos.x, vtx2_pixmap_pos.y);
		vtx1_pixmap_pos.x += REN_WIDTH / 2;
		vtx1_pixmap_pos.y += REN_HEIGHT / 2;
		vtx2_pixmap_pos.x += REN_WIDTH / 2;
		vtx2_pixmap_pos.y += REN_HEIGHT / 2;
if (i == 104) printf("\t(%d, %d) ; (%d, %d)\n", vtx1_pixmap_pos.x, vtx1_pixmap_pos.y, vtx2_pixmap_pos.x, vtx2_pixmap_pos.y);
		if (point_in_bounds(vtx1_pixmap_pos.x, vtx1_pixmap_pos.y) &&
			point_in_bounds(vtx2_pixmap_pos.x, vtx2_pixmap_pos.y))
		{
//printf("expose bresenham\n\t(%d,%d); (%d,%d)\n", vtx1_pixmap_pos.x, vtx1_pixmap_pos.y, vtx2_pixmap_pos.x, vtx2_pixmap_pos.y);
			bresenham(ctrl, vtx1_pixmap_pos, vtx2_pixmap_pos);
		}
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, //0, 0);
								-HALF_DRENWIN_WIDTH, -HALF_DRENWIN_HEIGHT);
	return (0);
}
