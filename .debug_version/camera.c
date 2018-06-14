/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:31:44 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/11 00:31:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#if 0
//TODO fix function for translation
void			cam_to_mat(t_mat_4b4 result, t_camera cam)
{
	t_mat_3b3	tmp;

	mat33_set(
	result[0] = cam.axis_x[0];
	result[1] = cam.axis_x[1];
	result[2] = cam.axis_x[2];
	result[3] = 0.;

	result[4] = cam.axis_y[0];
	result[5] = cam.axis_y[1];
	result[6] = cam.axis_y[2];
	result[7] = 0.;

	result[8] = cam.axis_z[0];
	result[9] = cam.axis_z[1];
	result[10] = cam.axis_z[2];
	result[11] = 0.;

//	vec3_sub(tmp, cam.anchor, cam.pos); //TODO verif
	result[12] = 0.;//tmp[0];
	result[13] = 0.;//tmp[1];
	result[14] = 0.;//tmp[2];
	result[15] = 1.;
}

	result[0] = tmp[0];
	result[4] = tmp[1];
	result[8] = tmp[2];
	result[3] = 0.;

	result[1] = tmp[3];
	result[5] = tmp[4];
	result[9] = tmp[5];
	result[7] = 0.;

	result[2] = tmp[6];
	result[6] = tmp[7];
	result[10] = tmp[8];
	result[11] = 0.;

#endif

void			cam_to_mat(t_mat_4b4 result, t_camera const cam)
{
	t_mat_3b3	tmp;


printf("\t cam to mat axis_x : (%f, %f, %f)\n", cam.axis_x[0], cam.axis_x[1], cam.axis_x[2]);
printf("\t cam to mat axis_y : (%f, %f, %f)\n", cam.axis_y[0], cam.axis_y[1], cam.axis_y[2]);
printf("\t cam to mat axis_z : (%f, %f, %f)\n", cam.axis_z[0], cam.axis_z[1], cam.axis_z[2]);
	mat33_set(tmp, cam.axis_x, cam.axis_y, cam.axis_z);

	result[0] = tmp[0];
	result[1] = tmp[1];
	result[2] = tmp[2];
	result[3] = 0.;

	result[4] = tmp[3];
	result[5] = tmp[4];
	result[6] = tmp[5];
	result[7] = 0.;

	result[8] = tmp[6];
	result[9] = tmp[7];
	result[10] = tmp[8];
	result[11] = 0.;

	t_vec_3d v;
	vec3_sub(v, cam.anchor, cam.world_pos); //TODO verif
	result[12] = v[0];
	result[13] = v[1];
	result[14] = v[2];
	result[15] = 1.;
	mat44_inv(result, result);
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
printf("polar pos input: (%f, %f, %f)\n", polar_cam_pos[0], polar_cam_pos[1], polar_cam_pos[2]);
	vec3_cpy(result.polar_pos, polar_cam_pos);
	vec3_polar_to_cartesian(result.world_pos, polar_cam_pos);
printf("\tcam world pos : (%f, %f, %f)\n", result.world_pos[0], result.world_pos[1], result.world_pos[2]);

	vec3_set(result.anchor, 0., 0., 0.);

printf("\tcam anchor pos : (%f, %f, %f)\n", result.anchor[0], result.anchor[1], result.anchor[2]);
	vec3_sub(result.axis_x, result.world_pos, result.anchor);
	vec3_normalize(result.axis_x, result.axis_x);
printf("\tcam axis_x : (%f, %f, %f)\n", result.axis_x[0], result.axis_x[1], result.axis_x[2]);
	vec3_set(result.axis_z, 0., 0., 1.);
	vec3_cross(result.axis_y, result.axis_z, result.axis_x);
	vec3_normalize(result.axis_y, result.axis_y);
printf("\tcam axis_y : (%f, %f, %f)\n", result.axis_y[0], result.axis_y[1], result.axis_y[2]);
	vec3_cross(result.axis_z, result.axis_y, result.axis_x);
	vec3_normalize(result.axis_z, result.axis_z);
printf("\tcam axis_z : (%f, %f, %f)\n", result.axis_z[0], result.axis_z[1], result.axis_z[2]);

//	vec3_scale(result.axis_x, result.polar_pos[0], result.axis_x);
//	vec3_scale(result.axis_y, result.polar_pos[0], result.axis_y);
//	vec3_scale(result.axis_z, result.polar_pos[0], result.axis_z);
//printf("\tcam axis_x : (%f, %f, %f)\n", result.axis_x[0], result.axis_x[1], result.axis_x[2]);
//printf("\tcam axis_y : (%f, %f, %f)\n", result.axis_y[0], result.axis_y[1], result.axis_y[2]);
//printf("\tcam axis_z : (%f, %f, %f)\n", result.axis_z[0], result.axis_z[1], result.axis_z[2]);

	return (result);
}
#endif

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
printf("polar pos input: (%f, %f, %f)\n", polar_cam_pos[0], polar_cam_pos[1], polar_cam_pos[2]);
	vec3_cpy(result.polar_pos, polar_cam_pos);
	vec3_polar_to_cartesian(result.world_pos, polar_cam_pos);
printf("\tcam world pos : (%f, %f, %f)\n", result.world_pos[0], result.world_pos[1], result.world_pos[2]);

	vec3_set(result.anchor, 0., 0., 0.);

printf("\tcam anchor pos : (%f, %f, %f)\n", result.anchor[0], result.anchor[1], result.anchor[2]);
	vec3_sub(result.axis_x, result.world_pos, result.anchor);
	vec3_normalize(result.axis_x, result.axis_x);
printf("\tcam axis_x : (%f, %f, %f)\n", result.axis_x[0], result.axis_x[1], result.axis_x[2]);
	vec3_set(result.axis_z, 0., 0., 1.);
	vec3_cross(result.axis_y, result.axis_z, result.axis_x);
	vec3_normalize(result.axis_y, result.axis_y);
printf("\tcam axis_y : (%f, %f, %f)\n", result.axis_y[0], result.axis_y[1], result.axis_y[2]);
	vec3_cross(result.axis_z, result.axis_x, result.axis_y);
	vec3_normalize(result.axis_z, result.axis_z);
	vec3_scale(result.axis_z, -1., result.axis_z);
printf("\tcam axis_z : (%f, %f, %f)\n", result.axis_z[0], result.axis_z[1], result.axis_z[2]);

//	vec3_scale(result.axis_x, result.polar_pos[0], result.axis_x);
//	vec3_scale(result.axis_y, result.polar_pos[0], result.axis_y);
//	vec3_scale(result.axis_z, result.polar_pos[0], result.axis_z);
//printf("\tcam axis_x : (%f, %f, %f)\n", result.axis_x[0], result.axis_x[1], result.axis_x[2]);
//printf("\tcam axis_y : (%f, %f, %f)\n", result.axis_y[0], result.axis_y[1], result.axis_y[2]);
//printf("\tcam axis_z : (%f, %f, %f)\n", result.axis_z[0], result.axis_z[1], result.axis_z[2]);

	return (result);
}
