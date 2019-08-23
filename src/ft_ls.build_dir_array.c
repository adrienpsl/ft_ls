#include <ft_ls..h>
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

static void update_if_bigger(char *new, int *old)
{
	int size;

	size = ft_strlen(new);
	if (size > *old)
		*old = size;
}

void add_max_length(t_file *file, t_length *length)
{
	update_if_bigger(file->uid, &length->uid);
	update_if_bigger(file->gid, &length->gid);
	update_if_bigger(file->size, &length->size);
	update_if_bigger(file->hardlink_nb, &length->hard_link);
	update_if_bigger(file->name, &length->name);
}

char *build_full_path(char *dir_path, char *name)
{
	static char full_path[2064];

	{
		ft_strcat(full_path, dir_path);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, name);
	}
	return (full_path);
}

struct stat *get_stat(char *path, int mode)
{
	static struct stat fs;
	int ret;

	if (mode == STAT)
		ret = stat(path, &fs);
	else
		ret = lstat(path, &fs);
	return (ret ? NULL : &fs);
}

t_file *
fill_file_element(char *full_path, char *file_name, t_ls_options *options,
	t_length *length)
{
	static t_file file;
	struct stat *fs;
	ft_bzero(&file, sizeof(t_file));

	if (
		(fs = get_stat(full_path, options->av_mode))
		)
	{
		add_type(&file, fs->st_mode);
		add_right(file.type + 1, fs->st_mode);
		add_acl_extended(file.type + 9, full_path);
		add_hardlink_size(&file, fs);
		add_uid_gid(&file, fs);
		add_file_and_link_name(&file, file_name);
		add_sort_param(&file, fs, options);
		add_time(file.sort_data, file.time, options);
		add_max_length(&file, length);
		return (&file);
	}
	else
		return (NULL);
}

t_array *build_dir_array(char *dir_path, t_ls_options *options)
{
	DIR *dir;
	struct dirent *dp;
	t_file *file;
	t_array *array;

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
		if (
			(file = fill_file_element(
				build_full_path(dir_path, dp->d_name),
				dp->d_name, options, NULL))
			)
			ft_array$push(&array, file);
	}
	return (array);
}
