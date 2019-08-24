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

#include <ft_ls..h>
# include "string.h"

void build_dir_list(t_file *file, t_ls *ls)
{
	t_array *array;

	array = build_dir_array(file->name, &ls->options, NULL);
}

void print_file_argv(t_array *array, t_ls_options *options)
{
	t_array *files;

	ft_array$func(array, ls_parsing$first_dir_func, NULL);
	if (array->i > 0)
	{
		if (
			(files = ft_array$slice_and_remove(array, 0,
											   array->i))
			)
		{
			options->long_format ?
			ft_array$func(files, line_print_long, options)
								 :
			ft_array$func(files, line_print, options);
			ft_array$free(&files);
		}
	}
}

int handle_r(char *path, t_file *file, t_ls_options *options)
{
	t_array *files;
	t_length length;
	char full_path[2064];

	ft_bzero(full_path, 2064);
	ft_bzero(&length, sizeof(t_length));
	if (*path)
	{
		ft_strcat(full_path, path);
		ft_strcat(full_path, "/");
	}
	ft_strcat(full_path, file->name);

	ft_printf("\n%s:\n", full_path);
	if (
		(files = build_dir_array(full_path, options, &length))
		)
	{// TODO : mettre ici option if all format
		options->long_format ?
		ft_array$func(files, line_print_long, &length)
							 :
		ft_array$func(files, line_print, &length);

		files->i = 2;
		while (
			(file = ft_array$next(files))
			)
		{
			if (file->is_dir)
			{
				handle_r(full_path, file, options);
			}
		}

		ft_array$free(&files);
	}
	else
		ft_dprintf(2, "ls: %s: %s\n", file->name, strerror(errno));

	return (0);
}

int ft_ls(char **av)
{
	t_ls ls;
	t_file *tmp;
	t_array *array;

	ft_bzero(&ls, sizeof(ls));
	ls.buffer.fd = 1; // for the speed
	ls$catch_options(&av, &ls.options);

	// test if . is get good handling

	array = ls$build_av_array(&ls.options, av, &ls.length);
	print_file_argv(array, &ls.options);
	array->i = 0;
	while ((tmp = ft_array$next(array)))
	{
		handle_r("", tmp, &ls.options);
	}

	return (0);
}

//  if pas argv


