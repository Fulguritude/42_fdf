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

void			toggle_debug(t_control *ctrl)
{
	ctrl->debug = !(ctrl->debug);
}

void			exit_error(char *e_msg, int e_no)
{
	if (e_no == 0)
		write(1, e_msg, ft_strlen(e_msg));
	else
		perror(e_msg);
	exit(e_no);
}

/*
** Bits per pixel (32, each color is an int) are immediately converted to
** bytes per pixel.
*/

static void		init_mlx(t_control *ctrl)
{
	if (!(ctrl->mlx_ptr = mlx_init()))
		exit_error("could not init mlx_ptr", 0);
	if (!(ctrl->win_ptr = mlx_new_window(ctrl->mlx_ptr,
				WIN_WIDTH, WIN_HEIGHT, "FdF")))
		exit_error("could not init win_ptr", 0);
	if (!(ctrl->img_ptr = mlx_new_image(ctrl->mlx_ptr, REN_WIDTH, REN_HEIGHT)))
		exit_error("could not init img_ptr", 0);
	if (!(ctrl->img_data = mlx_get_data_addr(ctrl->img_ptr, &(ctrl->img_bpp),
										&(ctrl->img_bpl), &(ctrl->endian))))
		exit_error("could not retrieve img data ptr and other info", 0);
	ctrl->img_bpp = ctrl->img_bpp / 8;
	ctrl->img_bytelen = ctrl->img_bpp * REN_HEIGHT * REN_WIDTH;
}

int				main(int argc, char **argv)
{
	t_control	ctrl;
	t_vec_3d	init_polar_cam_pos;

	if (argc <= 1)
		exit_error("usage: \"./fdf filepath/to/fdf/map.fdf\"\n", 0);
	init_mlx(&ctrl);
	ctrl.debug = 0;
	ctrl.fdf = init_fdf(argv[1]);
	vec3_set(init_polar_cam_pos, 2., 0., HALF_PI);
	ctrl.cam = init_cam(init_polar_cam_pos);
	ctrl.proj = &isometric_proj;
	mlx_key_hook(ctrl.win_ptr, handle_key, &ctrl);
	mlx_mouse_hook(ctrl.win_ptr, handle_mouse, &ctrl);
	mlx_expose_hook(ctrl.win_ptr, handle_redraw, &ctrl);
	mlx_loop(ctrl.mlx_ptr);
	return (0);
}
