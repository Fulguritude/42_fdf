/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:14:38 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/19 15:19:04 by tduquesn         ###   ########.fr       */
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

void			show_debug_info(t_control *ctrl)
{
	char	*str;

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
	str = ctrl->proj == isometric_proj ? "isometric" : "error";
	str = ctrl->proj == orthogonal_proj ? "orthogonal" : str;
	str = ctrl->proj == topdown_proj ? "topdown" : str;
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, HALF_DRENWIN_WIDTH + 20,
		HALF_DRENWIN_HEIGHT + 80, GREEN, str);
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

	if (argc != 2)
		exit_error("usage: \"./fdf [filepath/to/fdf/map.fdf]\"\n", 0);
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
