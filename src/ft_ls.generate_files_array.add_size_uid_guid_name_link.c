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

#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include "ft_ls..h"

static void add_size(t_file *file, struct stat *fs)
{
	if (
		file->type[0] == 'b' || file->type[0] == 'c'
		)
	{
		ft_sprintf(file->size, "%3d,", major(fs->st_rdev));
		{
			minor(fs->st_rdev) > 255 ?
			ft_sprintf(file->size, "%10x", minor(fs->st_rdev))
									 :
			ft_sprintf(file->size, "%4d", minor(fs->st_rdev));
		}
	}
	else
		ft_sprintf(file->size, "%d", fs->st_size);
}

static void add_uid_gid(t_file *file, struct stat *fs)
{
	// handle the n option
	ft_strcat(file->uid, getpwuid(fs->st_uid)->pw_name);
	ft_strcat(file->gid, getgrgid(fs->st_gid)->gr_name);
}

static void
add_file_and_link_name(t_file *file, struct stat *fs, char *full_path,
	char *file_name)
{
	ft_strcat(file->name, file_name);
	if ((S_IFMT & fs->st_mode) == S_IFLNK)
		readlink(full_path, file->link, PATH_MAX);
}

void
ls$add_size_uid$guid_name_link(t_file *file, struct stat *fs, char *full_path,
	char *file_name)
{
	add_size(file, fs);
	add_uid_gid(file, fs);
	add_file_and_link_name(file, fs, full_path, file_name);
}
