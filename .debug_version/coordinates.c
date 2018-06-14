/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:55:50 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/01 02:56:02 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"


#include <stdio.h>


void		vec3_polar_to_cartesian(t_vec_3d result, t_vec_3d const src)
{
	t_float		r;
	t_float		sin_lat;

printf("\t\tpolar source  vector is : (%f, %f, %f)\n", src[0], src[1], src[2]);
	r = src[0];
	sin_lat = sin(src[2]);
	result[0] = r * cos(src[1]) * sin_lat;
	result[1] = r * sin(src[1]) * sin_lat;
	result[2] = r * cos(src[2]);
printf("\t\tnew cartesian vector is : (%f, %f, %f)\n", result[0], result[1], result[2]);
}

/*
** Longitude is East/west, latitude is north/south
** TODO: 
*/

void		vec3_cartesian_to_polar(t_vec_3d result, t_vec_3d const src)
{	
	t_float		r;
	t_float		x;
	t_float		lat;
	t_float		lon;

	r = sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
	if (r == 0.)
	{
		write(2, "null vec3 cannot be converted to polar coordinates\n", 31);
		vec3_set(result, 0., 0., 0.);
		return ;
	}
	x = src[0] == 0. ? 0.001 : src[0];
if (x == 0 || x != x || r != r) printf("wtf in cartesian to polar\n");
	lon = atan(src[1] / x);
	lat = acos(src[2] / r);
if (lat != lat || lon != lon) printf("wtf2 in cartesian to polar\n");
	result[0] = r;
	result[1] = lon;
	result[2] = lat;
}
