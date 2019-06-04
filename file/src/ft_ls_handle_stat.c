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

static void ft_ls_max(int *size_array, int nb, char *str)
{
	size_t size;
	static const char *base = "0123456789";
	char buff[30];

	if (str != NULL)
		ft_str_len(&size, str);
	else
	{
		ft_mem_set(&buff, 0, 30);
		ft_itoa_base(nb, base, buff, 0);
		ft_str_len(&size, buff);
	}
	if ((int) size > *size_array)
		*size_array = size;
}

/*
 * first if  : see n option in ls man
 * second if : the driver will add a column in the -l, I add that size
 * the syntax &arr[n] is used for better clarity, not for optimisation.
 * */
int ft_set_max(t_ls_2 *l, char *file_name)
{
	if (l->options & FT_LS_O_n)
	{
		ft_ls_max(&l->size[FT_LS____UID], l->fs.st_uid, NULL);
		ft_ls_max(&l->size[FT_LS___GUID], l->fs.st_gid, NULL);
	}
	else
	{
		ft_ls_max(&l->size[FT_LS____UID], 0, getpwuid(l->fs.st_uid)->pw_name);
		ft_ls_max(&l->size[FT_LS___GUID], 0, getgrgid(l->fs.st_gid)->gr_name);
	}
	if (FT_ISBLK(l->fs.st_mode) || FT_ISCHR(l->fs.st_mode))
	{
		ft_ls_max(&l->size[FT_LS_DRIVER], major(l->fs.st_rdev), NULL);
		ft_ls_max(&l->size[FT_LS___FILE], minor(l->fs.st_rdev), NULL);
		l->has_driver = 1;
	}
	ft_ls_max(&l->size[FT_LS___NAME], 0, file_name);
	ft_ls_max(&l->size[FT_LS_____HL], l->fs.st_nlink, NULL);
	ft_ls_max(&l->size[FT_LS___FILE], l->fs.st_size, NULL);
	return (0);
}

static void ft_get_sort_data(t_ls_2 *l, t_file *file)
{
	if (FT_LS_O_t & l->options)
		file->sort_data = l->fs.st_mtimespec.tv_sec;
	else if (FT_LS_O_u & l->options)
		file->sort_data = l->fs.st_atimespec.tv_sec;
	else if (FT_LS_O_c & l->options)
		file->sort_data = l->fs.st_ctimespec.tv_sec;
	else if (FT_LS_O_S & l->options)
		file->sort_data = l->fs.st_size;
}

// TODO : implement continue for option A
/*
 * browse and save the name of the file, and the size of each column
 * the first char keep is the file is an directory.
 * */
int array_file_name(t_ls_2 *l)
{
	struct dirent *dp;
	size_t file_name_size;
	t_file *arr_p;

	if (ft_api_dir(l))
		return (-1);
	l->path[l->end_path++] = '/';
	while ((dp = readdir(l->dir)) != NULL)
	{
		if (!(l->options & FT_LS_O_a) && dp->d_name[0] == '.')
			continue;
		ft_str_len(&file_name_size, dp->d_name);
		ft_mem_copy(l->path + l->end_path, dp->d_name, file_name_size);
		ft_mem_copy(l->file, dp->d_name, file_name_size);
		if ((arr_p = ft_array_next_el(l->array)) == NULL || ft_api_lstat(l))
			return (-1);
		if (l->options & FT_LS_CUSTOM_SORT)
			ft_get_sort_data(l, arr_p);
		ft_mem_copy(arr_p->name, dp->d_name, file_name_size);
		ft_set_max(l, dp->d_name);
		ft_mem_set(l->path + l->end_path, 0, file_name_size);
		l->total += l->fs.st_blocks;
	}
	closedir(l->dir);
	return (0);
}
