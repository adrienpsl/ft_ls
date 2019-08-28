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

#include <ft_ls.h>

static int is_file(void *element, void *param)
{
	t_file *file;

	(void)param;
	file = element;
	return (file->type[0] != 'd');
}

void print_files(t_ls *ls)
{
	if (ls->av_directories->length)
	{
		if (
			(ls->av_files =
				 ftarray__extract_by_func(ls->av_directories, is_file, NULL))
			)
		{
			ls__print(ls->av_files, &ls->options, &ls->length, 0);
		}
	}
}

int ft_ls(char **av)
{
	t_ls ls = { .options= { .is_first = 1 }};

	if (
		ls__catch_options(&av, &ls.options)
		||
		!(ls.av_directories = ls__build_av_files(av, &ls.options, &ls.length))
		)
		return (-1);
	print_files(&ls);
	ftarray__set_start(ls.av_directories);
	while (
		(ls.dir = ftarray__next(ls.av_directories))
		)
	{
		if (ls.av_files->length && ls.dir->type[0] == 'd')
		{
			ls.options.is_first = 0;
			printf("%s:\n", ls.dir->name);
		}
		ls__loop_on_files("", ls.dir, &ls.options);
	}
	return (0);
}

