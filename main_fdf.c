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

int		t_color_to_colorint(t_color color)
{
	t_u32		res;

	res = color.blue;
	res |= color.green << 8;
	res |= color.red << 16;
	return ((int)res);
}

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
	t_control	*ctrl;

	ctrl = (t_control*)param;
	printf("mouse: %d, (%d, %d), %p\n", button, x, y, param);
	if (button == L_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, RED);
	else if (button == R_CLICK)
		mlx_pixel_put(ctrl->mlx_ptr, ctrl->win_ptr, x, y, BLUE);
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

//TODO loop_hook(void *param); //called when no event occurs


int		main(void)
{
	t_control ctrl;

	ctrl.mlx_ptr = mlx_init();
	ctrl.win_ptr = mlx_new_window(ctrl.mlx_ptr, 400, 300, "FdF");
	mlx_key_hook(ctrl.win_ptr, handle_key, &ctrl);
	mlx_mouse_hook(ctrl.win_ptr, handle_mouse, &ctrl);
	mlx_loop(ctrl.mlx_ptr);
}
