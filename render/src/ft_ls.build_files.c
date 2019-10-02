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

#include "ft_ls.build_files.h"
#include <ft_ls.h>

int			ls__files_sort_func(void *a, void *b, void *p_param)
{
	t_file		*f_1;
	t_file		*f_2;
	int			ret;
	t_options	*options;

	f_1 = a;
	f_2 = b;
	options = p_param;
	if ((options->sort_size || options->sort_status_change
		|| options->sort_time)
		&& f_1->sort_data != f_2->sort_data)
		ret = f_1->sort_data < f_2->sort_data;
	else
		ret = ft_strcmp(f_1->name, f_2->name) > 0;
	return (options->reverse ? !ret : ret);
}

int			fill_file(t_bf *bf, int source)
{
	ft_bzero(&bf->file, sizeof(t_file));
	if (OK == (source == AV_INPUT && !bf->options->long_format ?
		stat(bf->full_path, &bf->fs) :
		lstat(bf->full_path, &bf->fs)))
	{
		add_type(&bf->file, bf->fs.st_mode, bf->length);
		add_right(bf->file.type + 1, bf->fs.st_mode);
		add_acl_extended_attribute(bf->file.type + 10, bf->full_path);
		add_nb_hard_link(&bf->file, &bf->fs);
		add_size_or_drivers(&bf->file, &bf->fs);
		add_uid_gid(&bf->file, &bf->fs, bf->options);
		add_link_name(&bf->file, &bf->fs, bf->full_path, bf->file_name);
		add_total_size(bf);
		add_sort_param(&bf->file, &bf->fs, bf->options);
		add_time(bf->file.time_nb, bf->file.time, bf->options);
		add_max_length(&bf->file, bf->length, source);
		return (0);
	}
	else
		return (1);
}

void		init_bf(t_bf *bf, t_options *options, t_length *length)
{
	ft_bzero(bf, sizeof(t_bf));
	bf->options = options;
	bf->length = length;
}

int			add_path_name(t_bf *bf, char *dir_path, char *name)
{
	bf->full_path[0] = '\0';
	bf->file_name[0] = '\0';
	ftstr__add_buffer(bf->full_path, dir_path, dir_path ? "/" : NULL, name);
	ft_strcat(bf->file_name, name);
	return (0);
}

t_array		*ls__build_files(
	char *dir_path, t_options *options, t_length *length)
{
	t_bf bf;

	init_bf(&bf, options, length);
	if (NULL == (bf.dir = opendir(dir_path))
		|| NULL == (bf.files = ftarray__init(100, sizeof(t_file))))
		return (NULL);
	while ((bf.dp = readdir(bf.dir)))
	{
		if (0 == options->all && (bf.dp->d_name[0] == '.'))
			continue ;
		add_path_name(&bf, dir_path, bf.dp->d_name);
		fill_file(&bf, READDIR_INPUT);
		ftarray__push(bf.files, &bf.file);
	}
	closedir(bf.dir);
	ftarray__sort_bubble(bf.files, ls__files_sort_func, options);
	return (bf.files);
}
