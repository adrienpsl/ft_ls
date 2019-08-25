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

static t_file *
fill_file_element(char *full_path, char *file_name, t_options *options,
	t_length *length)
{
	static t_file file;
	struct stat *fs;
	ft_bzero(&file, sizeof(t_file));

	if (
		(fs = get_stat(full_path, options->av_mode))
		)
	{
		ls$add_type_right_acl_hardlink(&file, fs, full_path);
		ls$add_size_uid$guid_name_link(&file, fs, full_path, file_name);
		ls$add_sort$param_time_max$length(&file, fs, options, length);
		length->total += fs->st_blocks;
		return (&file);
	}
	else
		return (NULL);
}

static char *build_full_path(char *dir_path, char *name)
{
	static char full_path[2064] = { 0 };

	ft_bzero(full_path, 2064);
	ft_strcat(full_path, dir_path);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, name);
	return (full_path);
}

static int ls_array$sort_func(void *a, void *b, void *p_param)
{
	t_file *f_1;
	t_file *f_2;
	int ret;
	t_options *options;

	f_1 = a;
	f_2 = b;
	options = p_param;

	if (
		options->custom_sort
		&& f_1->sort_data != f_2->sort_data
		)
		ret = f_1->sort_data < f_1->sort_data;
	else
		ret = ft_str_cmp(f_1->name, f_2->name) > 0;
	return (options->reverse ? !ret : ret);
}

t_array *
ls$generate_files_array(char *dir_path, t_options *options, t_length *length)
{
	struct dirent *dp;
	DIR *dir;
	t_array *files;
	t_file *file;

	if (NULL == (dir = opendir(dir_path))
		|| NULL == (files = ft_array$init(100, sizeof(t_file))))
		return (NULL);
	while ((dp = readdir(dir)))
		if (
			0 == (dp->d_name[0] == '.' && !options->all)
			&& (file = fill_file_element(
				build_full_path(dir_path, dp->d_name), dp->d_name,
				options, length))
			)
			ft_array$push(&files, file);
	ft_array$sort_bubble(files, ls_array$sort_func, options);
	return (files);
}


