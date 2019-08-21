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

t_array *build_dir_array(char *dir_path, t_ls *ls);

int test_print(void *p_el, void *param)
{
	t_file *file;
	t_length *length;

	length = param;
	file = p_el;

	printf("%s%*s  %*s  %*s %*s %s %s\n",
		   file->type,
		   length->hard_link, file->hardlink_nb,
		   length->uid, file->uid,
		   length->gid, file->gid,
		   length->size, file->size,
		   file->time,
		   file->name);
	return (0);
}

void test_ls$get_dir_array()
{
	t_ls ls;
	t_array *array = build_dir_array("/Users/adpusel/test_ls",
									 &ls);
	ls.reverse_sorting = 0;
	ft_array$sort_bubble(array, ls_array$sort_func, &ls.reverse_sorting);
	ft_array$func(array, test_print, &ls.length);

	// test la list directory avec:
}