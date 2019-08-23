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
#include "ft_ls.build_dir_array.h"

void print_time(long int time_nb, char *out, t_ls_options *options)
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
	ft_memcpy(out, ctime(&time_nb) + 4, 12);
	if (active_year)
		ft_memcpy(out + 7, ctime(&time_nb) + 19, 5);
	//	if ((option & FT_LS_O_T) /*&& active_year*/)
	//	{
	//		ft_mem_copy(out, ctime(&time_nb) + 4, 20);
	//		ret = 20;
	//	}
}

/*
**	return a time for the last if not custom sorting
*/
unsigned long set_sort_param(t_ls_options *options, struct stat *fs)
{
	if (options->sort_time)
		return fs->st_mtimespec.tv_sec;
	else if (options->sort_status_change)
		return (fs->st_ctimespec.tv_sec);
	else if (options->sort_size)
		return (fs->st_size);
	else
		return (fs->st_atimespec.tv_sec);
}

void add_sort_param_and_time(t_bda *bda, t_ls *ls)
{
	{
		bda->file.sort_data = set_sort_param(&ls->options, &bda->fs);
	}
	print_time(bda->file.sort_data, bda->file.time, &ls->options);
}

int ls_array$sort_func(void *a, void *b, void *p_param)
{
	t_file *f_1;
	t_file *f_2;
	int ret;
	int *param;

	f_1 = a;
	f_2 = b;
	param = p_param;

	if (f_1->sort_data != f_2->sort_data)
		ret = f_1->sort_data < f_1->sort_data;
	else
		ret = ft_str_cmp(f_1->name, f_2->name) > 0;
	return (*param ? !ret : ret);
}