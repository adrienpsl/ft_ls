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

int ls_parsing_first_dir_func(void *p_el, void *param)
{
	(void)param;
	t_file *file;

	file = p_el;
	return (
		file->is_dir
	);
}

// faire une
void print_file(t_array *array, t_options *options, t_length *length)
{
	t_array *files;

	ftarray__func(array, ls_parsing_first_dir_func, NULL);
	if (array->i > 0)
	{
		if (
			(files = ftarray__slice_and_remove(array, 0,
											   array->i))
			)
		{
			options->is_first = 0;
			ls$print(files, options, length, 0);
			ftarray__free(&files);
		}
	}
}

// add each element in files and sort

// split the array between file and array element
// - print les files

// loop on these elements to build the list.

int ft_ls(char **av)
{
	t_options options = { .is_first = 1 };
	t_length length = { 0 };
	t_file *tmp;
	t_array *av_files;

	if (
		ls$catch_options(&av, &options)
		|| !(av_files = ls__build_av_files(av, &options, &length))
		)
		return (-1);
//	print_file(av_files, &options, &length);
	av_files->i = 0;
	if (av_files->length > 1 && options.is_first)
		printf("%s:\n", ((t_file*)av_files->data)->name);
	while (
		(tmp = ftarray__next(av_files))
		)
	{
		ls$handle_files_array("", tmp, &options);
	}
	return (0);
}

