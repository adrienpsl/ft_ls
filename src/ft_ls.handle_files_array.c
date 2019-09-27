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

static char	*build_path(char *full_path, char *path, t_file *file)
{
	ft_bzero(full_path, 2064);
	if (*path)
	{
		ft_strcat(full_path, path);
		if (full_path[ft_strlen(full_path) - 1] != '/')
			ft_strcat(full_path, "/");
	}
	ft_strcat(full_path, file->name);
	return (full_path);
}

static void	print_path(char *full_path, t_options *options)
{
	if (options->print_path == PRINT_FIRST)
		ft_printf("%s:\n", full_path);
	else if (options->print_path == PRINT)
		ft_printf("\n%s:\n", full_path);
	options->print_path = PRINT;
}

static void	do_recursive(char *full_path, t_options *options, t_array *files)
{
	t_file *file;

	files->i = 0;
	if (options->recursif)
	{
		while ((file = ftarray__next(files)))
		{
			if (file->type[0] == 'd' && ft_strcmp(file->name, ".") &&
				ft_strcmp(file->name, ".."))
			{
				ls__loop_on_files(full_path, file, options);
			}
		}
	}
}

int			ls__loop_on_files(char *path, t_file *file, t_options *options)
{
	t_array		*files;
	t_length	length;
	char		full_path[2064];

	ft_bzero(&length, sizeof(t_length));
	build_path(full_path, path, file);
	print_path(full_path, options);
	if ((files = ls__build_files(full_path, options, &length)))
	{
		ls__print(files, options, &length, 1);
		do_recursive(full_path, options, files);
		ftarray__free(&files);
	}
	else
		ft_dprintf(2, "ls: %s: %s\n", file->name, strerror(errno));
	return (0);
}
