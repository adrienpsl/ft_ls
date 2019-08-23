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
#include "ft_ls..h"

void add_hardlink_size(t_file *file, struct stat *fs)
{
	ft_itoa_unsigned(fs->st_nlink, BASE_10, file->hardlink_nb);
	ft_itoa_unsigned(fs->st_size, BASE_10, file->size);
}

void add_uid_gid(t_file *file, struct stat *fs)
{
	ft_strcat(file->uid, getpwuid(fs->st_uid)->pw_name);
	ft_strcat(file->gid, getgrgid(fs->st_gid)->gr_name);
}

void add_file_and_link_name(t_file *file, char *file_name)
{
	ft_strcat(file->name, file_name);
}


