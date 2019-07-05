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

static void type_size_uid_guid(t_ls *l)
{
	char buff[30];

	ft_ls_get_permission(l->fs.st_mode, buff);
	ft_get_acl_extended(l->path, buff + 10);
	ft_buffer_add(l->buff, buff, 11);
	ft_sprintf(l->buff, " %*d ", l->size[FT_LS_____HL], l->fs.st_nlink);
	if (l->options & FT_LS_O_n)
	{
		l->size[FT_LS____UID] = (l->size[FT_LS____UID] == 1) ? 3 : l->size[FT_LS____UID];
		l->size[FT_LS___GUID] = (l->size[FT_LS___GUID] == 1) ? 3 : l->size[FT_LS___GUID];
		ft_sprintf(l->buff, "%-*d", l->size[FT_LS____UID], l->fs.st_uid);
		ft_sprintf(l->buff, "%-*d", l->size[FT_LS___GUID], l->fs.st_gid);
	}
	else
	{
		ft_sprintf(l->buff, "%-*s",
				   l->size[FT_LS____UID], getpwuid(l->fs.st_uid)->pw_name);
		ft_sprintf(l->buff, "  %-*s  ",
				   l->size[FT_LS___GUID], getgrgid(l->fs.st_gid)->gr_name);
	}
}

static void ft_add_time(t_ls *l)
{
	int time_size;
	char buffer[24];

	if (FT_LS_O_u & l->options)
		time_size = print_time(l->fs.st_atimespec.tv_sec, buffer, l->options);
	else if (FT_LS_O_c & l->options)
		time_size = print_time(l->fs.st_ctimespec.tv_sec, buffer, l->options);
	else
		time_size = print_time(l->fs.st_mtimespec.tv_sec, buffer, l->options);
	ft_buffer_add(l->buff, buffer, time_size);
}

static void ft_add_size(t_ls *l)
{
	if (S_ISBLK(l->fs.st_mode) || S_ISCHR(l->fs.st_mode))
	{
		(l->size[FT_LS___FILE] = 4);
		(l->size[FT_LS_DRIVER] = 3);
		ft_sprintf(l->buff, "%*d,",
				   l->size[FT_LS_DRIVER], major(l->fs.st_rdev));
		if (minor(l->fs.st_rdev) > 255)
			ft_sprintf(l->buff, " %0*x ",
					   10, minor(l->fs.st_rdev));
		else
			ft_sprintf(l->buff, "%*d ",
					   l->size[FT_LS___FILE], minor(l->fs.st_rdev));
	}
	else
	{
		if (l->has_driver)
			ft_sprintf(l->buff, "%*ld ",
					   l->size[FT_LS___FILE] + 4, l->fs.st_size);
		else
			ft_sprintf(l->buff, "%*ld ",
					   l->size[FT_LS___FILE], l->fs.st_size);
	}
}

static int name_symlink(t_ls *l)
{
	ft_sprintf(l->buff, " %s", l->f->name);
	if (FT_ISLNK(l->fs.st_mode))
		ft_sprintf(l->buff, " -> %s", l->link_ptr);
	return (0);
}

int print_stats(t_ls *l)
{
	ft_mem_set(l->link_ptr, 0, PATH_MAX);
	if (FT_ISLNK(l->fs.st_mode)
		&& readlink(l->path, l->link_ptr, PATH_MAX) == -1)
		return (-1);
	type_size_uid_guid(l);
	ft_add_size(l);
	ft_add_time(l);
	name_symlink(l);
	ft_buffer_add(l->buff, "\n", 1);
	return (0);
}
