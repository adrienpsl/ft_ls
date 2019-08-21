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

#include "ft_ls.build_dir_array.h"
#include <dirent.h>

static void update_if_bigger(char *new, int *old)
{
	int size;

	size = ft_strlen(new);
	if (size > *old)
		*old = size;
}

static void update_max_length(t_file *file, t_length *length)
{
	update_if_bigger(file->uid, &length->uid);
	update_if_bigger(file->gid, &length->gid);
	update_if_bigger(file->size, &length->size);
	update_if_bigger(file->hardlink_nb, &length->hard_link);
}

void
fill_file_element(t_bda *bda, t_ls *ls)
{
	ft_bzero(&bda->file, sizeof(t_file));

	// TODO : check if the return
	lstat(bda->full_path, &bda->fs);
	{
		ls$get_file_attribute(bda->file.type, bda->full_path, bda->fs.st_mode);
	}
	{
		add_hardlink_size(bda);
	}
	{
		add_uid_gid(bda);
	}
	{
		add_file_and_link_name(bda);
	}
	{
		add_sort_param_and_time(bda, ls);
	}
	{
		update_max_length(&bda->file, &ls->length);
	}
}



t_array *build_dir_array(char *dir_path, t_ls *ls)
{
	t_bda bda;

	ft_bzero(&bda, sizeof(t_bda));
	// TODO : need to handle error ?
	if (
		NULL == (bda.dir = opendir(dir_path))
		|| NULL == (bda.array = ft_array$init(100, sizeof(t_file)))
		)
		return (NULL);
	while (
		(bda.dp = readdir(bda.dir))
		)
	{
		{
			ft_strcat(bda.full_path, dir_path);
			ft_strcat(bda.full_path, "/");
			ft_strcat(bda.full_path, bda.dp->d_name);
		}
		fill_file_element(&bda, ls);
		ft_array$push(&bda.array, &bda.file);
	}
	return (bda.array);
}