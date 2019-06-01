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

int ft_ls_option_parse(char *arg_str, t_ls *ls)
{
	return ft_io_catch_options(arg_str, "Rlart", &ls->options);
}

char *get_time(long int *time, int mode, char *out)
{
	if (mode)
		ft_mem_copy(out, ctime(time) + 4, 12);
	out[12] = 0;

	return (0);
}

static void norme_size_driver(t_file *f, t_ls *l)
{
	if (f->file_mode[0] == 'b' || f->file_mode[0] == 'c')
	{
		ft_sprintf(l->buff, "   %*d,",
				   l->size_coll[DRIVER_MAX_SIZE],
				   f->driver[FT_LS_DRIVER_MAX]);
		ft_sprintf(l->buff, "%*d",
				   (l->size_coll[SIZE_SIZE]
					- (l->size_coll[DRIVER_MAX_SIZE] + 1)),
				   f->size);
	}
	else
		ft_sprintf(l->buff, "  %*d", l->size_coll[SIZE_SIZE], f->size);
}

int buffer_add_line(t_file *f, t_ls *l)
{
	char time[20];

	ft_mem_set(time, 0, 20);
	get_time(&f->mtime, 1, time);
	ft_sprintf(l->buff, "%s", f->file_mode);
	ft_sprintf(l->buff, "  %-*d", l->size_coll[HARD_LINK_SIZE], f->hard_link);
	ft_sprintf(l->buff, " %*s", l->size_coll[UID_SIZE], f->uid);
	ft_sprintf(l->buff, "  %*s", l->size_coll[GUID_SIZE], f->guid);
	norme_size_driver(f, l);
	ft_sprintf(l->buff, " %s", time);
	ft_sprintf(l->buff, " %s", f->name);
	if (f->file_mode[0] == 'l')
		ft_sprintf(l->buff, " -> %s", f->sym_real_file);
	return (0);
}

int handle_lstast(char *path, t_file *f, t_ls *l)
{
	static struct stat fs;

	if (lstat(path, &fs))
		return (-1);
	if (FT_ISLNK(fs.st_mode))
		if (readlink(path, f->sym_real_file, FILE_NAME_MAX_SIZE) == -1)
			return (-1);
	ft_fill_line(&fs, f, l);
	return (0);
}


//int loop_directory(DIR *dir, t_array *array, char *before_path)
//{
//	t_file *file;
//	struct dirent *dp;
//	char path[PATH_MAX + 1];
//	size_t path_end;
//
//	path_end = ft_str_len(before_path);
//	ft_mem_set(&path, 0, PATH_MAX + 1);
//	ft_mem_copy(path, before_path, path_end);
//	path[path_end] = '/';
//	while ((dp = readdir(dir)) > 0)
//	{
//		file = ft_array_next_el(array);
//		file->name_size = ft_str_len(dp->d_name);
//		ft_mem_copy(file->name, dp->d_name, file->name_size);
//
////		ft_str_join(&path, "test/", link1->name);
//
////		ft_fill_link(path, link1, &ls);
////		nb_elements++;
//	}
//	return (0);
//}

//int ft_read_directory(char *path, t_array *array_sort)
//{
//	t_ls ls;
//	DIR *dir;
////	t_array *array;
//
//
//	ft_mem_set(&ls, 0, sizeof(t_ls));
//	if (!(dir = opendir(path)))
//		return (-1);
////	loop_directory(dir, array_sort, path);
//
//
//	return (0);
//}