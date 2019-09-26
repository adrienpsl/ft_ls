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
#include "ft_ls.build_files.h"

void		add_size_or_drivers(t_file *file, struct stat *fs)
{
	if (file->type[0] == 'b' || file->type[0] == 'c')
	{
		ft_sprintf(file->size, "%3d, ", major(fs->st_rdev));
		{
			minor(fs->st_rdev) > 255 ?
			ft_sprintf(file->size, "0x%08x", minor(fs->st_rdev))
			:
			ft_sprintf(file->size, "%3d", minor(fs->st_rdev));
		}
	}
	else
		ft_sprintf(file->size, "%d", fs->st_size);
}

void		add_uid_gid(t_file *file, struct stat *fs, t_options *options)
{
	if (options->no_group)
		ft_strcat(file->uid, getpwuid(fs->st_uid)->pw_name);
	else if (options->numeric_group)
	{
		ft_sprintf(file->uid, "%d", fs->st_uid);
		ft_sprintf(file->gid, "%ld", fs->st_gid);
	}
	else
	{
		ft_strcat(file->uid, getpwuid(fs->st_uid)->pw_name);
		ft_strcat(file->gid, getgrgid(fs->st_gid)->gr_name);
	}
}

void		add_link_name(
	t_file *file, struct stat *fs, char *full_path, char *file_name)
{
	if ((S_IFMT & fs->st_mode) == S_IFLNK)
		readlink(full_path, file->link, PATH_MAX);
	ft_strcat(file->name, file_name);
}

void		add_total_size(t_bf *bf)
{
	bf->length->total += bf->fs.st_blocks;
}
