/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 06:10:38 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

t_u32		ft_vlqlen(t_vlq const vlq)
{
	t_u32	i;

	i = 0;
	while (ft_msb(vlq[i]))
		++i;
	return (++i);
}
