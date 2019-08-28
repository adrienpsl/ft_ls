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

int print_link(void *p_link, void *n)
{
	t_file *file;
	(void)n;

	file = p_link;
	ft_printf("%s || %d\n", file->name, file->is_dir);

	return (0);
}

int print_link_test(void *p_link, void *n)
{
	t_file *file;
	(void)n;

	file = p_link;
	printf("%s || %d\n", file->name, file->is_dir);

	return (0);
}

/*
 * printf("%s%*s  %*s  %*s %*s %s %s\n",
		   file->type,
		   length->hard_link, file->hardlink_nb,
		   length->uid, file->uid,
		   length->gid, file->gid,
		   length->size, file->size,
		   file->time,
		   file->name);
 *
 * */


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

int line_print(void *p_el, void *param)
{
	t_file *file;
	(void)param;
	file = p_el;

	printf("%s", file->name);
	printf("\n");
	return (0);
}

void **generate_arr_ptr(t_options *options, t_length *length)
{
	static void *tab[2] = { 0 };

	tab[0] = options;
	tab[1] = length;
	return (tab);
}