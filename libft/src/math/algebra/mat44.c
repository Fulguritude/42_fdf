/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat44.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 02:12:41 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/14 02:12:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

void			mat44_set(t_mat_4b4 result, t_mat_3b3 const tl33_bloc,
							 t_vec_3d const bl13, t_vec_4d const tr41)
{
	result[0] = tl33_bloc[0];
	result[1] = tl33_bloc[1];
	result[2] = tl33_bloc[2];
	result[3] = bl13[0];
	result[4] = tl33_bloc[3];
	result[5] = tl33_bloc[4];
	result[6] = tl33_bloc[5];
	result[7] = bl13[1];
	result[8] = tl33_bloc[6];
	result[9] = tl33_bloc[7];
	result[10] = tl33_bloc[8];
	result[11] = bl13[2];
	result[12] = tr41[0];
	result[13] = tr41[1];
	result[14] = tr41[2];
	result[15] = tr41[3];
}

/*
**	[ 0  4  8  12 ]
**  [ 1  5  9  13 ]
**  [ 2  6  10 14 ]
**	[ 3  7  11 15 ]
*/

void			mat44_transpose(t_mat_4b4 result, t_mat_4b4 const m)
{
	t_float		tmp[6];

	result[0] = m[0];
	result[5] = m[5];
	result[10] = m[10];
	result[15] = m[15];
	tmp[0] = m[4];
	tmp[1] = m[8];
	tmp[2] = m[12];
	tmp[3] = m[9];
	tmp[4] = m[13];
	tmp[5] = m[14];
	result[4] = m[1];
	result[8] = m[2];
	result[12] = m[3];
	result[9] = m[6];
	result[13] = m[7];
	result[14] = m[11];
	result[1] = tmp[0];
	result[2] = tmp[1];
	result[3] = tmp[2];
	result[6] = tmp[3];
	result[7] = tmp[4];
	result[11] = tmp[5];
}

void			mat44_subbloc33_ij(t_mat_3b3 result, t_mat_4b4 const m,
									int i, int j)
{
	int			found;
	int			k;

	if (i < 0 || i >= 4 || j < 0 || j >= 4)
	{
		write(2, "mat44_subbloc33_ij: incorrect i or j, returning 0 mat\n", 54);
		ft_bzero(result, T_MAT33_SIZE);
		return ;
	}
	found = -1;
	k = -1;
	while (++k < 16)
	{
		if (k / 4 == i)
			k += 3;
		else if (k % 4 != j)
			result[++found] = m[k];
	}
}

t_float			mat44_det(t_mat_4b4 const m)
{
	t_mat_3b3	tmp;
	t_float		result;

	mat44_subbloc33_ij(tmp, m, 0, 0);
	result = m[0] * mat33_det(tmp);
	mat44_subbloc33_ij(tmp, m, 1, 0);
	result -= m[1] * mat33_det(tmp);
	mat44_subbloc33_ij(tmp, m, 2, 0);
	result += m[2] * mat33_det(tmp);
	mat44_subbloc33_ij(tmp, m, 3, 0);
	result -= m[3] * mat33_det(tmp);
	return (result);
}

void			mat44_inv(t_mat_4b4 result, t_mat_4b4 const m)
{
	t_mat_4b4	tmp;
	t_mat_3b3	sub_mat;
	int			i;
	t_float		det33;
	t_float		det44;

	i = -1;
	det44 = 0.;
	while (++i < 16)
	{
		mat44_subbloc33_ij(sub_mat, m, i / 4, i % 4);
		det33 = mat33_det(sub_mat);
		if (i < 4)
			det44 += (i % 2) ? -m[i] * det33 : m[i] * det33;
		tmp[i] = ((i % 4) + (i / 4)) % 2 ? -det33 : det33;
	}
	mat44_transpose(result, tmp);
	if (det44 != 0.)
		mat44_scale(result, 1. / det44, result);
	else
	{
		write(2, "mat44_inv: null determinant\n", 28);
		ft_bzero(result, T_MAT44_SIZE);	
	}
}
