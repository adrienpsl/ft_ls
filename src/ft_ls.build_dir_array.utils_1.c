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
#include "ft_ls.h"
#include "ft_ls.build_dir_array.h"

void add_hardlink_size(t_bda *bda)
{
	ft_itoa_unsigned(bda->fs.st_nlink, BASE_10, bda->file.hardlink_nb);
	ft_itoa_unsigned(bda->fs.st_size, BASE_10, bda->file.size);
}

void add_uid_gid(t_bda *bda)
{
	ft_strcat(bda->file.uid, getpwuid(bda->fs.st_uid)->pw_name);
	ft_strcat(bda->file.gid, getgrgid(bda->fs.st_gid)->gr_name);
}

void add_file_and_link_name(t_bda *bda)
{
	ft_strcat(bda->file.name, bda->dp->d_name);
}


