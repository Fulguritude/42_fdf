/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 18:44:44 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/20 18:45:13 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGEBRA_H
# define ALGEBRA_H

# include <math.h>
# include <unistd.h>
# include "libft/hdr/libft_math.h"

typedef t_f32			t_float;

# define T_VEC_SIZE		12
# define T_MAT_SIZE		36

/*
**	[ 0 ]
**  [ 1 ]
**  [ 2 ]
*/
typedef	t_float		t_vec_3d[3];

/*
**	[ 0  3  6 ]
**  [ 1  4  7 ]
**  [ 2  5  8 ]
*/
typedef t_float		t_mat_3b3[9];

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

t_quat			hop_add(t_quat const q1, t_quat const q2);
t_quat			hop_conjugate(t_quat const q);
t_quat			hop_scaling_product(t_f32 const s, t_quat const q);
t_f32			hop_pure_dot_product(t_quat const q1, t_quat const q2);
t_f32			hop_dot_product(t_quat const q1, t_quat const q2);

t_f32			hop_quadnorm(t_quat const q);
t_f32			hop_norm(t_quat const q);
t_quat			hop_normalize(t_quat const q);
int				hop_is_pure(t_quat const q);
int				hop_is_real(t_quat const q);

int				hop_is_zero(t_quat const q);
t_quat			hop_invert(t_quat const q);
t_quat			hop_pure_cross_product(t_quat const q1, t_quat const q2);
t_quat			hop_hamilton_product(t_quat const q1, t_quat const q2);
t_f32			cos_of_angle(t_quat const q1, t_quat const q2);

t_quat			rotor_from_angle(t_f32 rad, t_quat axis);

#endif
