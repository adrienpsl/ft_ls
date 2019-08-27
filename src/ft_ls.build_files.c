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

# include "ft_ls.build_files.h"

int ls_array$sort_func(void *a, void *b, void *p_param)
{
	t_file *f_1;
	t_file *f_2;
	int ret;
	t_options *options;

	f_1 = a;
	f_2 = b;
	options = p_param;

	if (
		(options->sort_size || options->sort_status_change ||
		 options->sort_time)
		&& f_1->sort_data != f_2->sort_data
		)
		ret = f_1->sort_data < f_2->sort_data;
	else
		ret = ft_str_cmp(f_1->name, f_2->name) > 0;
	return (options->reverse ? !ret : ret);
}

int fill_file(t_bf *bf, int source)
{
	ft_bzero(&bf->file, sizeof(t_file));
	if (
		OK == (source == AV_INPUT ?
		 stat(bf->full_path, bf->fs)
							:
		 lstat(bf->full_path, bf->fs))
		)
	{
		add_type(bf->file, bf->fs->st_mode, bf->length);
		add_right(bf->file->type + 1, bf->fs->st_mode);
		add_acl_extended_attribut(bf->file->type + 10, bf->full_path);
		add_nb_hard_link(bf->file, bf->fs);
		add_size_or_drivers(bf->file, bf->fs);
		add_uid_gid(bf->file, bf->fs);
		add_link_name(bf->file, bf->fs, bf->full_path);
		add_total_size(bf);
		add_sort_param(bf->file, bf->fs, bf->options);
		add_time(bf->file->sort_data, bf->file->time, bf->options);
		add_max_length(bf->file, bf->length, source);
		return (0);
	}
	else
		return (1);
}

void init_bf(t_bf *bf, t_options *options, t_length *length)
{
	ft_bzero(bf, sizeof(t_bf));
	bf->options = options;
	bf->length = length;
}

t_array *ls$build_files(char *dir_path, t_options *options, t_length *length)
{
	t_bf bf;
	t_bf *s_bf = &bf;
	(void)s_bf;

	init_bf(&bf, options, length);
	if (NULL == (bf.dir = opendir(dir_path))
		|| NULL == (bf.files = ftarray__init(100, sizeof(t_file)))
		)
		return (NULL);
	while (
		(bf.dp = readdir(bf.dir))
		)
	{
		ftstr__add_buffer(bf.full_path, dir_path, "/", bf.dp->d_name);
		ft_strcat(bf.file_name, bf.dp->d_name);
		if (
			0 == options->all && 0 == (bf.dp->d_name[0] == '.')
			)
		{
			fill_file(&bf, READDIR_INPUT);
			ft_strcat(bf.file->name, bf.file_name);
			ftarray__push(&bf.files, bf.file);
		}
	}
	return (bf.files);
}


