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

static int get_acl_and_attr(char *path, t_file *f)
{
	acl_t acl;
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (acl > 0)
	{
		f->acl = 1;
		acl_free((void *) acl);
	}
	if (listxattr(path, NULL, 0, 0) > 0)
		f->attr = 1;
	return (0);
}

int init_lstat(t_file *f, t_ls *l)
{
	if (lstat(l->path, &l->fs))
		return (-1);
	if (FT_ISLNK(l->fs.st_mode))
		if (readlink(l->path, f->sym_real_file, FT_LS_MAX_FILE) == -1)
			return (-1);
	l->total += l->fs.st_blocks;
	return (0);
}

int build_files_array(t_ls *l)
{
	t_file *file;
	struct dirent *dp;
	size_t path_end;

	if (!(l->dir = opendir(l->path)))
		return (-1);
	ft_str_len(&path_end, l->path);
	l->path[path_end++] = '/';
	while ((dp = readdir(l->dir)) != NULL)
	{
		if (0
			|| !(file = ft_array_next_el(l->array))
			|| ft_str_len(&file->name_size, dp->d_name)
			|| ft_mem_copy(file->name, dp->d_name, file->name_size)
			|| ft_mem_copy(l->path + path_end, file->name, file->name_size)
			|| get_acl_and_attr(l->path, file)
			|| init_lstat(file, l)
			|| extract_lstat(&l->fs, file, l)
			|| ft_mem_set(l->path + path_end, 0, file->name_size)
				)
			return (-1);
	}
	closedir(l->dir);
	return (0);
}

int init_t_ls(char *path, t_ls *l)
{
	if (ft_buffer_new(&l->buff, 20640, 1))
	    return (-1);
	if (!(l->dir = opendir(path)))
		return (-1);
	while (readdir(l->dir))
		l->nb_elements++;
	closedir(l->dir);
	if (ft_array_new(&l->array, l->nb_elements, sizeof(t_file)))
		return (-1);
	ft_mem_copy(l->path, path, STRING_MODE);
	return (0);
}