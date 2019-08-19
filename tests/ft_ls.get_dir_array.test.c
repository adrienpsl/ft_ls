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

t_array *loop_current_directory(char *dir_path, t_ls *ls);

int test_print(void *p_el, void *param)
{
	t_file *file;

	(void)param;
	file = p_el;

	printf("%s %s %s %s %s %s\n",
		   file->type,
		   file->hardlink_nb,
		   file->uid,
		   file->gid,
		   file->size,
		   file->name);
	return (0);
}

void test_ls$get_dir_array()
{
	t_ls ls;
	t_array *array = loop_current_directory("/Users/adpusel/test_ls",
		&ls);
	ft_array$func(array, test_print, NULL);

	// test la list directory avec:
}