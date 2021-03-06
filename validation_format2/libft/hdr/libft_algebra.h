/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_algebra.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 18:44:44 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/28 17:57:48 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ALGEBRA_H
# define LIBFT_ALGEBRA_H

# include <math.h>
# include <unistd.h>
# include "libft_math.h"

# define HALF_PI		0x1.921fb54442d18p+0
# define PI				0x1.921fb54442d18p+1
# define TAU 			0x1.921fb54442d18p+2

# define T_VEC3_SIZE		12
# define T_VEC4_SIZE		16
# define T_MAT33_SIZE		36
# define T_MAT44_SIZE		64

/*
**	[ 0 ]
**  [ 1 ]
**  [ 2 ]
** /[ 3 ]
*/
typedef	t_float		t_vec_3d[3];
typedef t_float		t_vec_4d[4];

/*
**	[ 0  2  4 ]
**  [ 1  3  5 ]
*/
typedef t_float		t_mat_2b3[6];

/*
**	[ 0  3  6 ]
**  [ 1  4  7 ]
**  [ 2  5  8 ]
*/
typedef t_float		t_mat_3b3[9];

/*
**	[ 0  4  8  12 ]
**  [ 1  5  9  13 ]
**  [ 2  6  10 14 ]
**	[ 3  7  11 15 ]
*/
typedef t_float		t_mat_4b4[16];

/*
** Let H be a 4-dimensional algebra over R, with basis {1, i, j, k} such that
**		i * i == j * j == k * k == ijk == -1
** Note that multiplication of non-unit basis vectors is anticommutative.
** H is called the ring of quaternions.
**
** NB: quaternions are used in the code as ordered pairs [r, (x, y, z)] to make
**		the code more legible, where r is a "real" quaternion and (x,y,z) is
**		a "pure" quaternion.
*/
typedef struct	s_quat
{
	t_f32	r;
	t_f32	x;
	t_f32	y;
	t_f32	z;
}				t_quat;

typedef t_quat	t_unit_quat;

/*
** 3*1
*/
void			vec3_set(t_vec_3d result, t_float x, t_float y, t_float z);
void			vec3_cpy(t_vec_3d dest, t_vec_3d const src);
void			vec3_swap(t_vec_3d v1, t_vec_3d v2);
void			vec3_add(t_vec_3d result, t_vec_3d const v1, t_vec_3d const v2);
void			vec3_sub(t_vec_3d result, t_vec_3d const v1, t_vec_3d const v2);
void			vec3_scale(t_vec_3d result, t_float const s, t_vec_3d const v);
void			vec3_normalize(t_vec_3d result, t_vec_3d const v);
void			vec3_cross(t_vec_3d result,
							t_vec_3d const v1, t_vec_3d const v2);

/*
** 3*3
*/
void			mat33_set(t_mat_3b3 result, t_vec_3d const v0,
							t_vec_3d const v1, t_vec_3d const v2);
void			mat33_add(t_mat_3b3 result,
							t_mat_3b3 const ma, t_mat_3b3 const mb);
void			mat33_scale(t_mat_3b3 result, t_float const s,
							t_mat_3b3 const m);
void			mat33_app_vec(t_vec_3d result,
							t_mat_3b3 const m, t_vec_3d const v);
void			mat33_mul(t_mat_3b3 result,
							t_mat_3b3 const ma, t_mat_3b3 const mb);
t_float			mat33_det(t_mat_3b3 const m);
void			mat33_inv(t_mat_3b3 result, t_mat_3b3 const m);
void			mat33_transpose(t_mat_3b3 result, t_mat_3b3 const src);

/*
** 4*4
*/
void			mat44_add(t_mat_4b4 result,
							t_mat_4b4 const ma, t_mat_4b4 const mb);
void			mat44_scale(t_mat_4b4 result,
							t_float const s, t_mat_4b4 const m);
void			mat44_app_vec(t_vec_4d result,
							t_mat_4b4 const m, t_vec_4d const v);
void			mat44_mul(t_mat_4b4 result,
							t_mat_4b4 const ma, t_mat_4b4 const mb);
void			mat44_transpose(t_mat_4b4 result, t_mat_4b4 const m);
void			mat44_subbloc33_ij(t_mat_3b3 result, t_mat_4b4 const m,
							int i, int j);
void			mat44_inv(t_mat_4b4 result, t_mat_4b4 const m);

/*
** t_quat			hop_add(t_quat const q1, t_quat const q2);
** t_quat			hop_conjugate(t_quat const q);
** t_quat			hop_scaling_product(t_f32 const s, t_quat const q);
** t_f32			hop_pure_dot_product(t_quat const q1, t_quat const q2);
** t_f32			hop_dot_product(t_quat const q1, t_quat const q2);
**
** t_f32			hop_quadnorm(t_quat const q);
** t_f32			hop_norm(t_quat const q);
** t_quat			hop_normalize(t_quat const q);
** int				hop_is_pure(t_quat const q);
** int				hop_is_real(t_quat const q);
**
** int				hop_is_zero(t_quat const q);
** t_quat			hop_invert(t_quat const q);
** t_quat			hop_pure_cross_product(t_quat const q1, t_quat const q2);
** t_quat			hop_hamilton_product(t_quat const q1, t_quat const q2);
** t_f32			cos_of_angle(t_quat const q1, t_quat const q2);
**
** t_quat			rotor_from_angle(t_f32 rad, t_quat axis);
*/

#endif
