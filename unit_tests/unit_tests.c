#include "../fdf.h"

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
	str = ctrl->proj == isometric_proj ? "isometric" : "error";
	str = ctrl->proj == orthogonal_proj ? "orthogonal" : str;
	str = ctrl->proj == topdown_proj ? "topdown" : str;
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, HALF_DRENWIN_WIDTH + 20,
		HALF_DRENWIN_HEIGHT + 80, GREEN, str);
}


void		print_mat33(char const *hdr, t_mat_3b3 const mat)
{
	printf("%s\n", hdr);
	printf("\t[ %8f, %8f, %8f ]\n", mat[0], mat[3], mat[6]);
	printf("\t[ %8f, %8f, %8f ]\n", mat[1], mat[4], mat[7]);
	printf("\t[ %8f, %8f, %8f ]\n", mat[2], mat[5], mat[8]);
}

void		print_mat44(char const *hdr, t_mat_4b4 const mat)
{
	printf("%s\n", hdr);
	printf("\t[ %8f, %8f, %8f, %8f ]\n", mat[0], mat[4], mat[8], mat[12]);
	printf("\t[ %8f, %8f, %8f, %8f ]\n", mat[1], mat[5], mat[9], mat[13]);
	printf("\t[ %8f, %8f, %8f, %8f ]\n", mat[2], mat[6], mat[10], mat[14]);
	printf("\t[ %8f, %8f, %8f, %8f ]\n", mat[3], mat[7], mat[11], mat[15]);
}

int			main()
{
	t_mat_3b3	id33 = {1., 0., 0., 0., 1., 0., 0., 0., 1.};
	print_mat33("id33 :", id33);
	mat33_inv(id33, id33);
	print_mat33("id33 inverted:", id33);

	t_mat_3b3	test = {1., 1., 0., 1., 0., 1., 0., 1., 1.};
	t_mat_3b3	inv_test;
	print_mat33("test :", test);
	mat33_inv(inv_test, test);
	print_mat33("test^-1 :", inv_test);
	mat33_mul(inv_test, inv_test, test);
	print_mat33("test * test^(-1) :", inv_test);
	mat33_inv(test, test);
	mat33_inv(test, test);
	print_mat33("test twice inversed, should be same as initial test:", test);

	t_mat_3b3	test2 = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
	print_mat33("test :", test2);
	mat33_transpose(test2, test2);
	print_mat33("test transpose:", test2);


	t_mat_4b4	id44 = {1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1.};
	print_mat44("id44 :", id44);
	mat44_inv(id44, id44);
	print_mat44("id44 inverted:", id44);

	t_mat_4b4	test3 = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.};
	print_mat44("test3:", test3);
	mat44_transpose(test3, test3);
	print_mat44("test3 transpose", test3);
	mat44_subbloc33_ij(test, test3, 1, 2);
	print_mat33("test3_subbloc33_12\n", test);

	t_mat_4b4	test44 = {1.,1.,1.,0.,1.,1.,0.,1.,1.,0.,1.,1.,0.,1.,1.,1.};
	t_mat_4b4	inv_test44;
	print_mat44("test44:", test44);
	mat44_inv(inv_test44, test44);
	print_mat44("test44 inv", inv_test44);
	mat44_mul(test44, inv_test44, test44);
	print_mat44("test44 * inv_test44 == id ?", test44);

	

	return (0);
}
