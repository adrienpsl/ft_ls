#include <ft_ls.h>
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

#include "ft_ls.h"
#include <dirent.h>
# include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

// here the sort stuff


// here the size stuff, size will be more complex after with certain file

// here catch and fill the group / uid
// here the hard link stuff


int fill_file(t_array **array, char *dir_path, char *file_name)
{
	struct stat fs;
	t_file file;
	char full_path[2064] = { 0 };

	ft_bzero(&file, sizeof(t_file));
	ft_strcat(full_path, dir_path);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, file_name);

	// TODO : check if the return
	lstat(full_path, &fs);

	ft_itoa_unsigned(fs.st_nlink, BASE_10, file.hardlink_nb);
	ft_itoa_unsigned(fs.st_size, BASE_10, file.size);

	ft_strcat(file.uid, getpwuid(fs.st_uid)->pw_name);
	ft_strcat(file.gid, getgrgid(fs.st_gid)->gr_name);
	ls$get_file_information(file.type, full_path, fs.st_mode);
	ft_strcat(file.name, file_name);

	// tester if link
	return (
		ft_array$push(array, &file)
		);
}

t_array *loop_current_directory(char *dir_path, t_ls *ls)
{
	t_array *array = NULL;
	struct dirent *dp;
	DIR *dir;
	(void)ls;

	// TODO : need to handle error ?
	if (
		NULL == (dir = opendir(dir_path))
		|| NULL == (array = ft_array$init(100, sizeof(t_file)))
		)
		return (NULL);
	while (
		(dp = readdir(dir))
		)
	{
		fill_file(&array, dir_path, dp->d_name);
	}
	return (array);
}