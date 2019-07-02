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

/*
 * init and malloc an array to handle the file
 * return an error if can't open directory.
 * */
int ft_ls_init(char *path, t_ls *l, t_buffer *buff, long options)
{
	ft_mem_set(l, 0, sizeof(t_ls));
	ft_mem_copy(l->path, path, STRING_MODE);
	ft_str_len(&l->end_path, path);
	l->options = options;
	if (ft_api_dir(l))
		return (-1);
	while (readdir(l->dir))
		l->elements++;
	closedir(l->dir);
	if (ft_array_new(&l->array, l->elements, sizeof(t_file)))
		return (-1);
	l->buff = buff;
	l->elements = 0;
	return (0);
}


void print_err(char *dir_name)
{
	static char buff[PATH_MAX + 10] = "ls: ";
	size_t dir_name_size;

	ft_str_len(&dir_name_size, dir_name);
	ft_mem_copy(buff + 4, dir_name, STRING_MODE);
	perror(buff);
}

int ft_handle_dir(char *path, int options, t_buffer *buff, char *dir_name)
{
	t_ls l;
	char full_path[PATH_MAX + 1];

	ft_mem_set(full_path, 0, PATH_MAX + 1);
	if (!ft_ls_init(path, &l, buff, options)
		&& !get_lstat_and_filename(&l)
		&& !ft_ls_sort(&l)
		&& !print_all(&l))
	{
		if (options & FT_LS_O_R)
			while ((l.f = ft_array_next_el(l.array)) != NULL)
			{
				if (l.f->dir && !(l.f->name[0] == '.' && l.f->name[1] == 0)
					&& !(l.f->name[0] == '.' && l.f->name[1] == '.'
						&& !l.f->name[2])
						)
				{
					ft_mem_copy(full_path, l.path, l.end_path);
					ft_mem_copy(full_path + l.end_path, l.f->name, STRING_MODE);
					ft_handle_dir(full_path, options, buff, l.f->name);
				}
			}
	}
	else
		print_err(dir_name);
	free(l.array);
	return (0);
}
