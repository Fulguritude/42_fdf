/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfpowi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:27:32 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

double		ft_lfpowi(double lf, int power)
{
	int			i;
	double		tmp;

	if (y == 0)
	   return (1.);
	tmp = ft_lfpowi(x, y / 2);
	if (y % 2 == 0)
		return (tmp * tmp);
	else
	{
		if (y > 0)
			return (x * tmp * tmp);
		else
			return (tmp * tmp / x);
	}
}
