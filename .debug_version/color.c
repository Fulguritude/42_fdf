/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 02:50:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/18 02:50:18 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


//	return (color.alpha << 24 | color.red << 16
//			| color.green << 8 | color.blue);
inline int		t_color_to_colorint(t_color color)
{
	return (*(int *)(&color));
}

t_color			new_color(t_u8 alpha, t_u8 red, t_u8 green, t_u8 blue)
{
	t_color		result;

	result.alpha = alpha;
	result.red = red;
	result.blue = blue;
	result.green = green;
	return (result);
}
