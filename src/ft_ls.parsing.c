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

# include <sys/stat.h>
# include <string.h>
# include "ft_ls..h"

static int add_link(t_array **array, char *path, struct stat *fs)
{
	static t_file file;

	ft_bzero(&file, sizeof(t_file));
	file.is_dir = S_ISDIR(fs->st_mode);
	ft_strcat(file.name, path);
	if (
		OK != ft_array$push(array, &file)
		)
		return (-1);
	return (0);
}

static int do_stat(char *path, t_ls_options *options, struct stat *fs)
{
	if (
		options->long_format ?
		lstat(path, fs) :
		stat(path, fs)
		)
	{
		ft_dprintf(2, "ls: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	else
	{
		return (0);
	}
}

static void loop_on_av(char **av, t_ls_options *options, t_array **array)
{
	struct stat fs;

	while (NULL != *av)
	{
		if (
			OK == do_stat(*av, options, &fs)
			)
		{
			add_link(array, *av, &fs);
		}
		av++;
	}
}

/**
 * @brief 	cette fonction va fill le dir array et le fil array de ls
 *
 * @param ls
 * @param av
 * @return
 */

t_array *build_list(t_ls *ls, char **av)
{
	t_array *dir_array;
	static char *no_argv[2] = { "." };

	if (
		NULL == (dir_array = ft_array$init(50, sizeof(t_file)))
		)
		return (NULL);
	loop_on_av(av, &ls->options, &dir_array);
	ft_array$sort_bubble(dir_array, ls_parsing$sort_func, NULL);
	ft_array$func(dir_array, ls_parsing$first_dir_func, NULL);

	if (dir_array->i > 0)
	{
		if (
			NULL == (ls->files = ft_array$slice_and_remove(dir_array, 0,
														   dir_array->i))
			);
	}
	else
		loop_on_av(no_argv, &ls->options, &dir_array);
		ls->dirs = dir_array;
	return (dir_array);
}
