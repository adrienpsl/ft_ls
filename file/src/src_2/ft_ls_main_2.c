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

int ft_api_lstat(t_ls_2 *l)
{
	if (lstat(l->path, &l->fs))
		return (-1);
	return (0);
}

int ft_api_dir(t_ls_2 *l)
{
	if (!(l->dir = opendir(l->path)))
		return (-1);
	return (0);
}

/*
 * init and malloc an array to handle the file
 * */
int init_ls_2(char *path, t_ls_2 *l)
{

	ft_mem_copy(l->path, path, STRING_MODE);
	if (ft_api_dir(l))
		return (-1);
	while (readdir(l->dir))
		l->elements++;
	closedir(l->dir);
	if (ft_array_new(&l->array, l->elements, sizeof(FT_LS_MAX_FILE)))
		return (-1);
	ft_str_len(&l->end_path, path);
	return (0);
}

void ls_free(t_ls_2 *l)
{
	if (l->array)
	    ft_array_free(&l->array);
	if (l->buff)
	    ft_buffer_free(&l->buff);
	memset(l, 0, sizeof(t_ls_2));
}

void ft_ls_max(int *size_array, int nb, char *str)
{
	size_t size;
	static const char *base = "0123456789";
	char buff[30];

	if (str)
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

int ft_set_max(t_ls_2 *l, char *file_name)
{
	ft_ls_max(FT_LS_NAME + l->size, 0, file_name);
	ft_ls_max(FT_LS_HL + l->size, l->fs.st_nlink, NULL);
	ft_ls_max(FT_LS_UID + l->size, 0, getpwuid(l->fs.st_uid)->pw_name);
	ft_ls_max(FT_LS_GUID + l->size, 0, getgrgid(l->fs.st_gid)->gr_name);
	ft_ls_max(FT_LS_FILE + l->size, l->fs.st_size, NULL);
	if (FT_ISBLK(l->fs.st_mode) || FT_ISCHR(l->fs.st_mode))
	{
		ft_ls_max(FT_LS_FILE + l->size, minor(l->fs.st_rdev), NULL);
		ft_ls_max(FT_LS_DRIVER + l->size, major(l->fs.st_rdev), NULL);
	}
	return (0);
}

/*
 * browse and save the name of the file, and the size of each column
 * the first char keep is the file is an directory.
 * */
int array_file_name(t_ls_2 *l)
{
	static struct dirent *dp;
	static size_t file_name_size;
	static void *arr_p;

	ft_api_dir(l);
	l->path[l->end_path++] = '/';
	while ((dp = readdir(l->dir)) != NULL)
	{
		ft_str_len(&file_name_size, dp->d_name);
		ft_mem_copy(l->path + l->end_path, dp->d_name, file_name_size);
		if ((arr_p = ft_array_next_el(l->array)) == NULL
			|| ft_api_lstat(l))
			return (-1);
		ft_set_max(l, dp->d_name);
		ft_mem_copy(arr_p, dp->d_name, file_name_size);
		ft_mem_set(l->path + l->end_path, 0, file_name_size);
	}
	closedir(l->dir);
	return (0);
}