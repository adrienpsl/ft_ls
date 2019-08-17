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
# include "ft_ls.h"

static int add_link(t_array **array, char *path, struct stat *fs)
{
	static t_file file;

	ft_bzero(&file, sizeof(t_file));
	file.dir = S_ISDIR(fs->st_mode);
	if (
		NULL == (file.name = ft_strdup(path))
		|| OK != ft_array$push(array, &file)
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

static int sort_func(void *a, void *b, void *param)
{
	(void)param;
	t_file *f_1;
	t_file *f_2;

	f_1 = a;
	f_2 = b;

	if (f_1->dir == f_2->dir)
	{
		return (ft_str_cmp(f_1->name, f_2->name) > 0);
	}
	else
		return (f_1->dir < f_2->dir ?  1 : 0);
}

t_array *build_list(t_ls *ls, char **av)
{
	t_array *array;
	struct stat fs;

	if (
		NULL == (array = ft_array$init(sizeof(t_file), 100))
		)
		return (NULL);
	while (NULL != *av)
	{
		if (
			OK == do_stat(*av, &ls->options, &fs)
			)
		{
			add_link(&array, *av, &fs);
		}
		av++;
	}
	ft_array$sort_bubble(array, sort_func, NULL);
	return (array);
}
