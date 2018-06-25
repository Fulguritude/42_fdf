/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:48 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:10 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

inline int		ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}
