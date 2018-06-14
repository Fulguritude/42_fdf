/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_products.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 21:44:21 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/04 21:44:40 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

/*
** HOP stands for Hypercomplex as Ordered Pair
**
** All following operators take quaternions to work as an ordered pair of a
** scalar and a 3D vector. 
*/

t_quat			hop_add(t_quat const q1, t_quat const q2)
{
	t_quat	res;

	res.r = q1.r + q2.r;
	res.x = q1.x + q2.x;
	res.y = q1.y + q2.y;
	res.z = q1.z + q2.z;
	return (res);
}

/*
** NB: The inverse of a unit quaternion (norm == 1 and pure) is its conjugate.
*/
t_quat			hop_conjugate(t_quat const q)
{
	t_quat	res;

	res.r = q.r;
	res.x = -q.x;
	res.y = -q.y;
	res.z = -q.z;
	return (res);
}

t_quat			hop_scaling_product(t_f32 const s, t_quat const q)
{
	t_quat	res;

	res.r = s * q.r;
	res.x = s * q.x;
	res.y = s * q.y;
	res.z = s * q.z;
	return (res);
}

/*
** Returns the dot product of the pure parts of q1 and q2
*/

inline t_f32	hop_pure_dot_product(t_quat const q1, t_quat const q2)
{
	return (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);
}

inline t_f32	hop_dot_product(t_quat const q1, t_quat const q2)
{
	return (q1.r * q2.r + hop_pure_dot_product(q1, q2));
}

inline t_f32	hop_quadnorm(t_quat const q)
{
	return (q.r * q.r + hop_pure_dot_product(q, q));
}

inline t_f32	hop_norm(t_quat const q)
{
	return (sqrt(hop_quadnorm(q)));
}

inline t_quat	hop_normalize(t_quat const q)
{
	return (hop_scaling_product(fast_inv_sqrt(hop_quadnorm(q)), q));
}

inline int		hop_is_pure(t_quat const q)
{
	return (!q.r);
}

inline int		hop_is_real(t_quat const q)
{
	return (!q.x && !q.y && !q.z);
}

inline int		hop_is_zero(t_quat const q)
{
	return (!q.r && !q.x && !q.y && !q.z);
}

t_quat			hop_invert(t_quat const q)
{
	if (hop_is_zero(q))
	{
		write(2, "hop_invert: cannot invert null quaternion\n", 42);
		return (q);
	}
	return (hop_scaling_product(1.0f / hop_quadnorm(q), hop_conjugate(q)));
}

/*
** Returns the cross product of the pure part of q1 and q2 inside a new pure
** quaternion.
*/

t_quat			hop_pure_cross_product(t_quat const q1, t_quat const q2)
{
	t_quat	pure;

	pure.r = 0;
	pure.x = q1.y * q2.z - q1.z * q2.y;
	pure.y = q1.z * q2.x - q1.x * q2.z;
	pure.z = q1.x * q2.y - q1.y * q2.x;
	return (pure);
}

t_quat			hop_hamilton_product(t_quat const q1, t_quat const q2)
{
	t_quat	res;

	res = hop_pure_cross_product(q1, q2);
	if (q1.r != 0)
		res = hop_add(hop_scaling_product(q1.r, q2), res);
	if (q2.r != 0)
		res = hop_add(hop_scaling_product(q2.r, q1), res);
	res.r = q1.r * q2.r - hop_pure_dot_product(q1, q2);
	return (res);
}

inline t_f32	cos_of_angle(t_quat const q1, t_quat const q2)
{
	return (hop_dot_product(q1, q2) * fast_inv_sqrt(hop_quadnorm(q1)) *
			fast_inv_sqrt(hop_quadnorm(q2)));
}

/*
** Convention uses radians. Axis shouldn't be normalized when sent to this
** function as this function handles the normalization: the math only work with
** a unit vector as the axis !
**
** Rotations are a rotor q times our quaternion we want to rotate p times
** the inverse of q in that order. It gives a result which is a pure quaternion
**
** q is of the form [cos(t/2); sin(t/2) * v] where v is a unit (pure) quaternion
** representing an axis around which to rotate in 3D. q is not pure, but is
** normalized.
**
** A unit quaternion is a pure quaternion with norm 1. A normalized (or
** "unit-norm") quaternion is a quaternion with norm 1.
*/

#if 0
t_quat			rotor_from_angle(t_f32 th_rad, t_quat axis)
{
	t_quat	res;
	t_quat	unit;
	t_f32	s;

	res.r = cos(th_rad / 2);
	s = sin(th_rad / 2);
	unit = hop_normalize(axis);
	//TODO
	return (unit);
}

/*
** This function forces interpretation of a quat as pure
*/
t_quat			rotate_purequat(t_quat p, t_f32 th_rad, t_list axis_lst)
{
	t_quat	result;
	t_quat	

	p.r = 0;
}
#endif
