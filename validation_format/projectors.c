/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 23:56:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/29 23:56:10 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

t_gridpoint		orthogonal_proj(t_vec_3d const v)
{
	t_gridpoint	res;

	res.x = v[0] + PROJ_CST1 * v[2];
	res.y = v[1] + PROJ_CST1_HLF * v[2];
	return (res);
}

t_gridpoint		isometric_proj(t_vec_3d const v)
{
	t_gridpoint	res;

	res.x = PROJ_CST1 * v[0] - PROJ_CST2 * v[1];
	res.y = PROJ_CST1_HLF * v[0] + PROJ_CST2_HLF * v[1] + v[2];
	return (res);
}

t_gridpoint		topdown_proj(t_vec_3d const v)
{
	t_gridpoint	res;

	res.x = v[0];
	res.y = v[1];
	return (res);
}

void		toggle_proj(t_control *ctrl)
{
	if (ctrl->proj == &isometric_proj)
		ctrl->proj = orthogonal_proj;
	else if (ctrl->proj == &orthogonal_proj)
		ctrl->proj = topdown_proj;
	else
		ctrl->proj = isometric_proj;
}
