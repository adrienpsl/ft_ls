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

#include "ft_ls..h"

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

int line_print_long(void *p_el, void *param)
{
	t_file *file;
	t_length *length;
	t_options *options;
	void **tab_ptr;

	tab_ptr = param;
	options = tab_ptr[0];
	length = tab_ptr[1];
	file = p_el;
	if (!options->all && file->name[0] == '.')
		return (0);
	if (options->all)
	{
		printf("%s ", file->type);
		printf("%*s ", length->hard_link, file->hardlink_nb);
		printf("%-*s  ", length->uid, file->uid);
		printf("%-*s  ", length->gid, file->gid);
		printf("%*s ", length->size, file->size);
		printf("%s ", file->time);
		printf("%s", file->name);
		if (file->link[0])
			printf(" -> %s", file->link);
	}
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