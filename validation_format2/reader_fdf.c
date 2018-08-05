/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 23:01:30 by fulguritu         #+#    #+#             */
/*   Updated: 2018/08/05 22:13:18 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Number of edges can be found by considering that graphing each cell's right
** and bottom boundary represents the whole grid, safe for the topmost and the
** leftmost lines.
**
** "if ((i + 1) % line_size != 0)" => there are line_nb times this is not true
*/

static void		build_all_edge_pairs(t_fdf *fdf, int line_nb, int line_size)
{
	int			k;
	int			i;
	t_edge		tmp;

	fdf->vtx_lst_len = line_nb * line_size;
	if (!(fdf->edge_lst = malloc(sizeof(t_edge) *
					(fdf->vtx_lst_len * 2 - line_nb - line_size))))
		exit_error("build_edges: malloc failure", errno);
	k = -1;
	i = -1;
	while (++i < fdf->vtx_lst_len)
		if ((i + 1) % line_size != 0)
		{
			tmp.vtx_from = &(fdf->vtx_lst[i]);
			tmp.vtx_to = &(fdf->vtx_lst[i + 1]);
			fdf->edge_lst[++k] = tmp;
		}
	i = -1;
	while (++i < fdf->vtx_lst_len - line_size)
	{
		tmp.vtx_from = &(fdf->vtx_lst[i]);
		tmp.vtx_to = &(fdf->vtx_lst[i + line_size]);
		fdf->edge_lst[++k] = tmp;
	}
	fdf->edge_lst_len = k + 1;
}

static t_fdf	build_fdf(char **file_data[MAX_LINE_NB], int line_nb)
{
	t_fdf		fdf;
	t_u32		min_line_size;
	int			i;
	int			j;

	min_line_size = MAX_LINE_SIZE;
	i = -1;
	while (++i < line_nb)
		if (ft_ptrarrlen(file_data[i]) < min_line_size)
			min_line_size = ft_ptrarrlen(file_data[i]);
	if (!(fdf.vtx_lst = malloc(sizeof(t_vertex) * line_nb * min_line_size)))
		exit_error("build_fdf: malloc failure", errno);
	i = -1;
	while (++i < line_nb)
	{
		j = -1;
		while (++j < (t_float)min_line_size)
			vec3_set(fdf.vtx_lst[i * min_line_size + j].world_pos,
					(t_float)j - min_line_size / 2., (t_float)i - line_nb / 2.,
					(t_float)ft_atoi(file_data[i][j]) / 10.);
	}
	fdf.vtx_lst_len = line_nb * min_line_size;
	build_all_edge_pairs(&fdf, line_nb, min_line_size);
	fdf.h_scale = INIT_H_SCALE;
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
		exit_error("init_fdf: call to std open failed", errno);
	line = NULL;
	line_nb = -1;
	while ((status = get_next_line(fd, &line)) != EOF_RD)
	{
		if (status == ERR_RD || !line)
			exit_error("init_fdf: error reading file in gnl", 0);
		if (++line_nb == MAX_LINE_NB)
			exit_error("init_fdf: file max line number exceeded", 0);
		file_data[line_nb] = ft_split(line, " ");
		ft_strdel(&line);
	}
	fdf = build_fdf(file_data, ++line_nb);
	while (--line_nb >= 0)
		ft_strlsdel(&(file_data[line_nb]));
	if (close(fd) == -1)
		exit_error("init_fdf: call to std close failed", errno);
	return (fdf);
}
