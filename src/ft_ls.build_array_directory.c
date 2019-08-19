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

#include <dirent.h>
#include "ft_ls.h"

// here get the file stuff



// here the hard link stuff



// here the sort stuff



// here catch and fill the group / uid


// here the size stuff, size will be more complex after with certain file



int fill_file(t_file *file, struct dirent *dp)
{
	struct stats stat;

	ft_bzero(file, sizeof(t_file));
	ft_strcat(file->name, dp->d_name);
	return (0);
}

t_array *build_array_directory(char *path, t_ls *ls)
{
	t_array *array = NULL;
	struct dirent *dp;
	DIR *dir;
	t_file file;


	// TODO : need to handle error ?
	if (
		NULL == (dir = opendir(path))
		|| NULL == (array = ft_array$init(100, sizeof(t_file)))
		)
	   return (NULL);
	while (
		(dp = readdir(dir))
		)
	{
		fill_file(&file, dp);
		ft_array$push(&array, &file);
	}
	return (array);
}