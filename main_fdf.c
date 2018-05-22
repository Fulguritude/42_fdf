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
	mlx_key_hook(ctrl.win_ptr, handle_key, &ctrl);
	mlx_mouse_hook(ctrl.win_ptr, handle_mouse, &ctrl);
	mlx_loop(ctrl.mlx_ptr);
}
