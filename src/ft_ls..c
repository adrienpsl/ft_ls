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

int ls_parsing$first_dir_func(void *p_el, void *param)
{
	(void)param;
	t_file *file;

	file = p_el;

	return (
		file->is_dir
	);
}

void print_file(t_array *array, t_options *options, t_length *length)
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
			options->is_first = 0;
			ft_array$func(files, line_print_long,
						  generate_arr_ptr(options, length));
			ft_array$free(&files);
		}
	}
}

int ft_ls(char **av)
{
	t_options options = { .is_first = 1 };
	t_length length = { 0 };
	t_file *tmp;
	t_array *argv;

	if (
		ls$catch_options(&av, &options)
		|| !(argv = ls$build_av_array(&options, av, &length))
		)
		return (-1);
	print_file(argv, &options, &length);
	argv->i = 0;
	while (
		(tmp = ft_array$next(argv))
		)
	{
		ls$handle_files_array("", tmp, &options);
	}
	return (0);
}

