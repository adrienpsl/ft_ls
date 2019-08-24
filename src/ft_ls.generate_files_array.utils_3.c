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
	//	if ((option & FT_LS_O_T) /*&& active_year*/)
	//	{
	//		ft_mem_copy(out, ctime(&time_nb) + 4, 20);
	//		ret = 20;
	//	}
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
		options->custom_sort
		&& f_1->sort_data != f_2->sort_data
		)
		ret = f_1->sort_data < f_1->sort_data;
	else
		ret = ft_str_cmp(f_1->name, f_2->name) > 0;
	return (options->reverse ? !ret : ret);
}