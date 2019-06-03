/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *get_time(long int *time, int mode, char *out)
{
	if (mode)
		ft_mem_copy(out, ctime(time) + 4, 12);
	out[12] = 0;

	return (0);
}

static void norme_size_driver(t_f *f, t_ls *l)
{
	int size;

	size = l->size_coll[FT_LS_DRIVER] ? l->size_coll[FT_LS___FILE] + 3
										 : l->size_coll[FT_LS___FILE];
	if (f->file_mode[0] == 'b' || f->file_mode[0] == 'c')
	{
		ft_sprintf(l->buff, "   %*d, ",
				   l->size_coll[FT_LS_DRIVER],
				   f->driver[FT_LS_DRIVER_MAX]);
		ft_sprintf(l->buff, "%*d",
				   (l->size_coll[FT_LS___FILE]
					- (l->size_coll[FT_LS_DRIVER] + 2)),
				   f->driver[FT_LS_DRIVER_MIN]);
	}
	else
		ft_sprintf(l->buff, "%*d", size, f->size);
}

int buffer_add_line(t_f *f, t_ls *l)
{
	char time[20];

	ft_mem_set(time, 0, 20);
	get_time(&f->mtime, 1, time);
	ft_sprintf(l->buff, "%s", f->file_mode);
	if (f->acl)
		ft_sprintf(l->buff, "+ ");
	else if (f->attr)
		ft_sprintf(l->buff, "@ ");
	else
		ft_sprintf(l->buff, "  ");
	ft_sprintf(l->buff, "%*d ", l->size_coll[FT_LS_____HL], f->hard_link);
	ft_sprintf(l->buff, "%-*s  ", l->size_coll[FT_LS____UID], f->uid);
	ft_sprintf(l->buff, "%-*s  ", l->size_coll[FT_LS___GUID], f->guid);
	norme_size_driver(f, l);
	ft_sprintf(l->buff, " %s", time);
	ft_sprintf(l->buff, " %s", f->name);
	if (f->file_mode[0] == 'l')
		ft_sprintf(l->buff, " -> %s", f->sym_real_file);
	ft_sprintf(l->buff, "\n");
	return (0);
}

//int buffer_no_long(t_file *f, t_ls *ls)
//{
//	struct ttysize	ts;
//	ts.ts_cols = 200;
//	int size;
//
////	if (size)
////	    ;
//	size = ts.ts_cols / ls->size_coll[FT_LS_NAME];
//
//
//	// check if all data fit in one line ?
//
//	// create the nb of col needed
//
//	// j'alloue un buffer de la taille de ma line * le nb de column
//	// je le fit, et ensuite je le print.
//	// j'avance dans mon array d'index a index pour trouver
//	// la ou je veux prendre mes datas.
//
//	// je get la tailles de la plus grand colunm
//	// je divise mon nombre d'elemen par cette column
//	// je vais devoir louper sur mon array * 2
//	// il font tous mois que la premier column ?
//	ioctl(0, TIOCGWINSZ, &ts);
//	return 0;
//}


int buffer_tab(t_ls *ls)
{
	t_f *file;

	ls->array->i = 0;
	while ((file = ft_array_next_el(ls->array)))
	{
	    buffer_add_line(file, ls);
	}
	return (0);
}










