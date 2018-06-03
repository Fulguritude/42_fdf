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


#if 0
/*
	vec3_set(result.pos, REN_WIDTH / 2, REN_HEIGHT / 2, 0);
	vec3_normalize(result.pos, result.pos);
*/
//vec3_set(result.polar_pos, 40., PI / 4., PI / 4.);
//vec3_polar_to_cartesian(result.pos, result.polar_pos);
////vec3_normalize(result.pos, result.pos);

	vec3_cpy(result.pos, polar_cam_pos);
	vec3_set(result.anchor, 0., 0., 0.);
	vec3_sub(result.axis_z, result.pos, result.anchor);
	vec3_normalize(result.axis_z, result.axis_z);
/*	if (ft_abs(result.axis_x[0]) < 0.001)
		result.axis_x[0] = 0.001;
	if (ft_abs(result.axis_x[1]) < 0.001)
		result.axis_x[1] = 0.001;
*/
t_vec_3d	tmp;
	vec3_set(tmp, 0., 1., 0.);
	vec3_cross(result.axis_y, tmp, result.axis_z);
	vec3_normalize(result.axis_y, result.axis_y);
	vec3_cross(result.axis_y, result.axis_z, result.axis_x);
//	vec3_normalize(result.axis_z, result.axis_z);
	return (result);
#endif

# define INIT_CAM_POS_X	-30.0
# define INIT_CAM_POS_Y	40.0
# define INIT_CAM_POS_Z -20.0
# define INIT_CAM_ANC_X	0.
# define INIT_CAM_ANC_Y	0.
# define INIT_CAM_ANC_Z	0.

t_camera		init_cam(t_vec_3d polar_cam_pos)
{
	t_camera	result;

/*
	vec3_set(result.pos, REN_WIDTH / 2, REN_HEIGHT / 2, 0);
	vec3_normalize(result.pos, result.pos);
*/
//vec3_set(result.polar_pos, 40., PI / 4., PI / 4.);
//vec3_polar_to_cartesian(result.pos, result.polar_pos);
////vec3_normalize(result.pos, result.pos);

printf("init_cam:\n");
printf("\tpolar pos input: (%f, %f, %f)\n", polar_cam_pos[0], polar_cam_pos[1], polar_cam_pos[2]);
	vec3_cpy(result.polar_pos, polar_cam_pos);
	vec3_polar_to_cartesian(result.world_pos, polar_cam_pos);
printf("\tworld pos : (%f, %f, %f)\n", result.world_pos[0], result.world_pos[1], result.world_pos[2]);

	vec3_set(result.anchor, 0., 0., 0.);

printf("\tworld pos : (%f, %f, %f)\n", result.world_pos[0], result.world_pos[1], result.world_pos[2]);
	vec3_sub(result.axis_x, result.world_pos, result.anchor);
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
	t_control	ctrl;
	t_vec_3d	init_polar_cam_pos;

	if (argc <= 1)
		exit_error("usage: \"./fdf filepath/to/fdf/map.fdf\"\n", 0);
	ctrl.mlx_ptr = mlx_init();
	ctrl.win_ptr = mlx_new_window(ctrl.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	ctrl.img_ptr = mlx_new_image(ctrl.mlx_ptr, REN_WIDTH, REN_HEIGHT);
	ctrl.img_data = mlx_get_data_addr(ctrl.img_ptr, &(ctrl.img_bpp),
										&(ctrl.img_bpl), &(ctrl.endian));
	ctrl.img_bpp = ctrl.img_bpp / 8;
	ctrl.img_bytelen = ctrl.img_bpp * REN_HEIGHT * REN_WIDTH;
	vec3_set(init_polar_cam_pos, 40., PI / 4., PI / 4.);
	ctrl.fdf = init_fdf(argv[1]);
	ctrl.cam = init_cam(init_polar_cam_pos);
	mlx_key_hook(ctrl.win_ptr, handle_key, &ctrl);
	mlx_mouse_hook(ctrl.win_ptr, handle_mouse, &ctrl);
	mlx_expose_hook(ctrl.win_ptr, handle_redraw, &ctrl);
	mlx_loop(ctrl.mlx_ptr);
}
