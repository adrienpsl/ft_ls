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

#include <sys/ttycom.h>
#include <sys/ioctl.h>
#include "ft_ls.h"
# include "string.h"

static char *build_path(char *full_path, char *path, t_file *file)
{
	ft_bzero(full_path, 2064);
	if (*path)
	{
		ft_strcat(full_path, path);
		ft_strcat(full_path, "/");
	}
	ft_strcat(full_path, file->name);
	return (full_path);
}

static void print_path(char *full_path, t_options *options)
{
	if (
		options->print_path == PRINT_FIRST
		)
		printf("%s:\n", full_path);
	else if (
		options->print_path == PRINT
		)
		printf("\n%s:\n", full_path);
	{
		options->print_path = PRINT;
	}
}

static void do_recursive(char *full_path, t_options *options, t_array *files)
{
	t_file *file;

	files->i = 0;
	if (
		options->recursif
		)
	{
		while (
			(file = ftarray__next(files))
			)
		{
			if (file->is_dir && ft_str_cmp(file->name, ".") &&
				ft_str_cmp(file->name, ".."))
			{
				ls__loop_on_files(full_path, file, options);
			}
		}
	}
}

int ls__loop_on_files(char *path, t_file *file, t_options *options)
{
	t_array *files;
	t_length length;
	char full_path[2064];

	ft_bzero(&length, sizeof(t_length));
	build_path(full_path, path, file);
	print_path(full_path, options);
	if (
		(files = ls__build_files(full_path, options, &length))
		)
	{
		ls__print(files, options, &length, 1);
		do_recursive(full_path, options, files);
		ftarray__free(&files);
	}
	else
		ft_dprintf(2, "ls: %s: %s\n", file->name, strerror(errno));
	return (0);
}