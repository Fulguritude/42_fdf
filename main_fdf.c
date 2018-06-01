/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:14:38 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/18 15:14:52 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#if 0
       int
       mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );

       int
       mlx_string_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string );
#endif


//TODO loop_hook(void *param); //called when no event occurs


void			exit_error(char *e_msg, int e_no)
{
	if (e_no == 0)
		write(1, e_msg, ft_strlen(e_msg));
	else
		perror(e_msg);
	exit(e_no);
}

/*
**
	t_vec_3d	pos;
	t_vec_3d	anchor;
	t_vec_3d	axis_x; //right
	t_vec_3d	axis_y; //up
	t_vec_3d	axis_z; //forward input eye
*/

# define INIT_CAM_POS_X	-30.0
# define INIT_CAM_POS_Y	40.0
# define INIT_CAM_POS_Z -20.0
# define INIT_CAM_ANC_X	0.
# define INIT_CAM_ANC_Y	0.
# define INIT_CAM_ANC_Z	0.

t_camera		init_cam()
{
	t_camera	result;

/*
	vec3_set(result.pos, REN_WIDTH / 2, REN_HEIGHT / 2, 0);
	vec3_normalize(result.pos, result.pos);
*/
	vec3_set(result.polar_pos, 40., PI / 4., PI / 4.);
	vec3_polar_to_cartesian(result.pos, result.polar_pos);
vec3_normalize(result.pos, result.pos);

	vec3_set(result.anchor, 0, 0, 0);
	vec3_sub(result.axis_x, result.pos, result.anchor);
	vec3_normalize(result.axis_x, result.axis_x);
/*	if (ft_abs(result.axis_x[0]) < 0.001)
		result.axis_x[0] = 0.001;
	if (ft_abs(result.axis_x[1]) < 0.001)
		result.axis_x[1] = 0.001;
*/
	vec3_set(result.axis_z, 0., 0., 1.);
	vec3_cross(result.axis_y, result.axis_x, result.axis_z);
	vec3_normalize(result.axis_y, result.axis_y);
	vec3_cross(result.axis_z, result.axis_x, result.axis_y);
	vec3_normalize(result.axis_z, result.axis_z);
	return (result);
}

/*
** Bits per pixel (32, each color is an int) are immediately converted to
** bytes per pixel.
*/

int				main(int argc, char **argv)
{
	t_control ctrl;

	if (argc <= 1)
		exit_error("usage: \"./fdf filepath/to/fdf/map.fdf\"\n", 0);
	ctrl.mlx_ptr = mlx_init();
	ctrl.win_ptr = mlx_new_window(ctrl.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	ctrl.img_ptr = mlx_new_image(ctrl.mlx_ptr, REN_WIDTH, REN_HEIGHT);
	ctrl.img_data = mlx_get_data_addr(ctrl.img_ptr, &(ctrl.img_bpp),
										&(ctrl.img_bpl), &(ctrl.endian));
	ctrl.img_bpp = ctrl.img_bpp / 8;
	ctrl.img_bytelen = ctrl.img_bpp * ctrl.img_bpl * REN_HEIGHT;
	ctrl.fdf = init_fdf(argv[1]);
	ctrl.cam = init_cam();
	mlx_key_hook(ctrl.win_ptr, handle_key, &ctrl);
	mlx_mouse_hook(ctrl.win_ptr, handle_mouse, &ctrl);
	mlx_expose_hook(ctrl.win_ptr, handle_redraw, &ctrl);
	mlx_loop(ctrl.mlx_ptr);
}
