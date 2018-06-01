/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 23:01:30 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/21 23:01:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

/*
** Number of edges can be found by considering that graphing each cell's right
** and bottom boundary represents the whole grid, safe for the topmost and the
** leftmost lines.
*/

static void		build_all_edge_pairs(t_fdf *fdf, int line_nb, int line_size)
{
	t_edge		*result;
	int			k;
	int			i;
//	int			j;
	t_edge		tmp;

//printf("\tedge_pairs\n");
	fdf->vtx_lst_len = line_nb * line_size;
	if (!(result = malloc(sizeof(t_edge) * (fdf->vtx_lst_len * 2 - line_nb - line_size))))
//	if (!(result = malloc(sizeof(t_edge) * ((line_nb - 1) +
//			(line_size - 1) + 2 * (line_nb - 1) * (line_size - 1)))))
		exit_error("malloc failure in build_edges", errno);
	k = -1;
	i = -1;
	while (++i < fdf->vtx_lst_len)
		if ((i + 1) % line_size != 0) //there are line_nb times this is not true 
		{
			tmp.vtx_from = &(fdf->vtx_lst[i]);
			tmp.vtx_to = &(fdf->vtx_lst[i + 1]);
			result[++k] = tmp;
		}
	i = -1;
	while (++i <= fdf->vtx_lst_len - line_size)
	{
		tmp.vtx_from = &(fdf->vtx_lst[i]);
		tmp.vtx_to = &(fdf->vtx_lst[i + line_size]);
		result[++k] = tmp;
	}
	fdf->edge_lst_len = k;
	fdf->edge_lst = result;
}

static t_fdf	build_fdf(char **file_data[MAX_LINE_NB], int line_nb)
{
	t_fdf		fdf;
	t_u32		min_line_size;
	t_vec_3d	tmp;
	int			i;

	min_line_size = (t_u32)(-1);
//printf("\tbuildfdf, line_nb %d\n", line_nb);
	i = -1;
	while (++i < line_nb)
		if (ft_ptrarrlen(file_data[i]) < min_line_size)
			min_line_size = ft_ptrarrlen(file_data[i]);
//printf("\tmin_line_size : %d\n", min_line_size);
	if (!(fdf.vtx_lst = malloc(sizeof(t_vertex) * line_nb * min_line_size)))
		exit_error("malloc failure in build_fdf", errno);
	tmp[1] = -1.;
	while (++tmp[1] < line_nb)
	{
		tmp[0] = -1.;
		while (++tmp[0] < (t_float)min_line_size)
		{
//printf("\t\tloop %d, %d, %d\n", (int)tmp[0], (int)tmp[1], (int)tmp[2]);
			tmp[2] = (t_float)ft_atoi(file_data[(int)tmp[1]][(int)tmp[0]]) / 10.;
			ft_memcpy(&(fdf.vtx_lst[(int)tmp[1] * min_line_size + (int)tmp[0]]),
						tmp, T_VEC3_SIZE);
		}
	}
	fdf.vtx_lst_len = line_nb * min_line_size;
	build_all_edge_pairs(&fdf, line_nb, min_line_size);
	return (fdf);
}

/*
** line is filepath in input, then recycled as a variable for norminette
*/

t_fdf			init_fdf(char *line)
{
	int		fd;
	t_fdf	fdf;
	char	**file_data[MAX_LINE_NB];
	int		status;
	int		line_nb;

	if ((fd = open(line, O_RDONLY)) == -1)
		exit_error("call to open failed", errno);
	line_nb = -1;
//printf("Debug1\n");
	while ((status = get_next_line(fd, &line)) != EOF_RD)
	{
		if (status == ERR_RD || !line)
			exit_error("error reading file in gnl, ignore this msg", errno);
		file_data[++line_nb] = ft_split(line, " ");
		free(line);
	}
//printf("Debug2\n");
	fdf = build_fdf(file_data, ++line_nb);
//printf("Debug3\n");
	while (--line_nb >= 0)
		ft_strlsdel(&(file_data[line_nb]));
	return (fdf);
}
