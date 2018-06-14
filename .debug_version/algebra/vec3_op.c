/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:16:11 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/30 14:16:24 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

void		vec3_set(t_vec_3d result, t_float x, t_float y, t_float z)
{
	result[0] = x;
	result[1] = y;
	result[2] = z;
}

void		vec3_cpy(t_vec_3d dest, t_vec_3d const src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

void		vec3_swap(t_vec_3d v1, t_vec_3d v2)
{
	t_vec_3d	tmp;

	tmp[0] = v2[0];
	tmp[1] = v2[1];
	tmp[2] = v2[2];
	v2[0] = v1[0];
	v2[1] = v1[1];
	v2[2] = v1[2];
	v1[0] = tmp[0];
	v1[1] = tmp[1];
	v1[2] = tmp[2];
}

void		vec3_add(t_vec_3d result, t_vec_3d const v1, t_vec_3d const v2)
{
	result[0] = v1[0] + v2[0]; 
	result[1] = v1[1] + v2[1];
	result[2] = v1[2] + v2[2];
}

void		vec3_sub(t_vec_3d result, t_vec_3d const v1, t_vec_3d const v2)
{
	result[0] = v1[0] - v2[0]; 
	result[1] = v1[1] - v2[1];
	result[2] = v1[2] - v2[2];
}

void		vec3_scale(t_vec_3d result, t_float const s, t_vec_3d const v)
{
	result[0] = s * v[0]; 
	result[1] = s * v[1];
	result[2] = s * v[2];
}

void		vec3_normalize(t_vec_3d result, t_vec_3d const v)
{
	t_f32		inv_norm;

	inv_norm = fast_inv_sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	result[0] = inv_norm * v[0];
	result[1] = inv_norm * v[1];
	result[2] = inv_norm * v[2];
}

void		vec3_cross(t_vec_3d result, t_vec_3d const v1, t_vec_3d const v2)
{
	t_vec_3d tmp;

	tmp[0] = v1[1] * v2[2] - v1[2] * v2[1]; 
	tmp[1] = v1[2] * v2[0] - v1[0] * v2[2];
	tmp[2] = v1[0] * v2[1] - v1[1] * v2[0];
	result[0] = tmp[0]; 
	result[1] = tmp[1];
	result[2] = tmp[2];
}

//TODO
/*
** Make fast and test
**
t_f32		fast_inv_sqrt(t_f32 f)
{
	long		i;
	t_f32		x2;
	t_f32		y;
	const t_f32 threehalfs = 1.5F;

	x2 = f * 0.5F;
	y  = f;
	i  = *(long *)(&y);
	i  = 0x5f3759df - (i >> 1);
	y  = *(t_f32 *)(&i);
	y  = y * (threehalfs - ( x2 * y * y ));
//	y  = y * (threehalfs - ( x2 * y * y ));
	return y;
}
**
*/
t_f32		fast_inv_sqrt(t_f32 f)
{
	return (1. / sqrt(f));
}
