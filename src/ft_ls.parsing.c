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

#include <sys/stat.h>
# include <string.h>
#include "ft_ls.h"

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
	return (array);
}




// si pas de data > je set a . et je lance un ls de tout ca
// more clear with one struct wich will stock all the data


//int ls$parsing(t_ls *ls, char **av)
//{
//	//	ft_array$init(100)
//	// si pas argv set .
//
//	// else do that
//	while (*av != NULL)
//	{
//		av++;
//	}
//}