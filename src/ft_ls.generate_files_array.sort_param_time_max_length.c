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

#include <time.h>
#include <ft_mem.h>
#include <ft_ls..h>
# include <sys/stat.h>

void add_time(long int time_nb, char *buffer, t_options *options)
{
	long int current_date;
	int active_year;
	(void)options;

	active_year = 0;
	current_date = time(NULL);
	if (current_date + 3600 <= time_nb)
		active_year = 1;
	if (current_date - 15778800 >= time_nb)
		active_year = 1;
	ft_memcpy(buffer, ctime(&time_nb) + 4, 12);
	if (active_year)
		ft_memcpy(buffer + 7, ctime(&time_nb) + 19, 5);
}

/*
**	return a time for the last if not custom sorting
*/
void add_sort_param(t_file *file, struct stat *fs, t_options *options)
{
	if (options->sort_time)
		file->sort_data = fs->st_mtimespec.tv_sec;
	else if (options->sort_status_change)
		file->sort_data = fs->st_ctimespec.tv_sec;
	else if (options->sort_size)
		file->sort_data = fs->st_size;
	else
		file->sort_data = fs->st_atimespec.tv_sec;
}

static void update_if_bigger(char *new, int *old)
{
	int size;

	size = ft_strlen(new);
	if (size > *old)
		*old = size;
}

static void add_max_length(t_file *file, t_length *length, t_options *options)
{
	if (options->is_argv && file->is_dir)
		return;
	update_if_bigger(file->uid, &length->uid);
	update_if_bigger(file->gid, &length->gid);
	update_if_bigger(file->size, &length->size);
	update_if_bigger(file->hardlink_nb, &length->hard_link);
	update_if_bigger(file->name, &length->name);
}

void
ls$add_sort$param_time_max$length(t_file *file, struct stat *fs,
	t_options *options, t_length *length)
{
	add_sort_param(file, fs, options);
	add_time(file->sort_data, file->time, options);
	add_max_length(file, length, options);
}