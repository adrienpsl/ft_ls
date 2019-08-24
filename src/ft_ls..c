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

int ls$handle_directory(char *path, t_file *file, t_options *options)
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
		(files = ls$generate_files_array(full_path, options, &length))
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
				ls$handle_directory(full_path, file, options);
			}
		}

		ft_array$free(&files);
	}
	else
		ft_dprintf(2, "ls: %s: %s\n", file->name, strerror(errno));
	return (0);
}

int ls_parsing$first_dir_func(void *p_el, void *param)
{
	(void)param;
	t_file *file;

	file = p_el;

	return (
		file->is_dir
	);
}

void print_file(t_array *array, t_options *options)
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

int ft_ls(char **av)
{
	t_options options = { 0 };
	t_length length = { 0 };
	t_file *tmp;
	t_array *array;

	if (
		ls$catch_options(&av, &options)
		|| !(array = ls$build_av_array(&options, av, &length))
		)
		return (-1);
	print_file(array, &options);
	array->i = 0;
	while (
		(tmp = ft_array$next(array))
		)
	{
		ls$handle_directory("", tmp, &options);
	}
	return (0);
}

