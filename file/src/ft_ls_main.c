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
 * */
int ft_ls_init(char *path, t_ls_2 *l, t_buff *buff, long options)
{
	ft_mem_set(l, 0, sizeof(t_ls_2));
	ft_mem_copy(l->path, path, STRING_MODE);
	if (ft_api_dir(l))
		return (-1);
	while (readdir(l->dir))
		l->elements++;
	closedir(l->dir);
	if (ft_array_new(&l->array, l->elements, sizeof(t_file)))
		return (-1);
	l->buff = buff;
	ft_str_len(&l->end_path, path);
	l->options = options;
	l->elements = 0;
	return (0);
}

void ft_ls_free(t_ls_2 *l)
{
	if (l->array)
		ft_array_free(&l->array);
	ft_mem_set(l, 0, sizeof(t_ls_2));
}

void print_err(char *dir_name)
{
	static char buff[PATH_MAX + 10] = "ls: ";
	size_t dir_name_size;

	ft_str_len(&dir_name_size, dir_name);
	ft_mem_copy(buff + 4, dir_name, STRING_MODE);
	perror(buff);
}

int ft_all(char *path, int options, t_buff *buff, char *dir_name)
{
	t_ls_2 l;
	char full_path[PATH_MAX + 1];

	if (!ft_ls_init(path, &l, buff, options)
		&& !array_file_name(&l) && !ft_ls_sort(&l) && !print_all(&l))
	{
		if (options & FT_LS_O_R)
			while ((l.f = ft_array_next_el(l.array)) != NULL)
			{
				if (l.f->directory && ft_mem_cmp(l.f->name, ".", 2)
					&& ft_mem_cmp(l.f->name, "..", 3))
				{
					ft_mem_set(full_path, 0, PATH_MAX + 1);
					ft_mem_copy(full_path, l.path, l.end_path);
					ft_mem_copy(full_path + l.end_path, l.f->name, STRING_MODE);
					ft_all(full_path, options, buff, l.f->name);
				}
			}
	}
	else
		print_err(dir_name);
	ft_ls_free(&l);
	return (0);
}

