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

#include <sys/ioctl.h>
#include "ft_ls..h"

static int print_long(void *el, void *param)
{
	t_file *file;
	t_length *length;

	file = el;
	length = param;
	printf("%s ", file->type);
	printf("%*s ", length->hard_link, file->hardlink_nb);
	printf("%-*s  ", length->uid, file->uid);
	printf("%-*s  ", length->gid, file->gid);
	printf("%*s ", length->size, file->size);
	printf("%s ", file->time);
	printf("%s", file->name);
	if (file->link[0])
		printf(" -> %s", file->link);
	printf("\n");
	return (0);
}

void ls$print_col(t_array *files, t_length *length, t_options *options)
{
	struct ttysize ts;
	int col_size;
	int line_size;
	t_file *file;
	int i = 0;
	int y = 0;

	ioctl(0, TIOCGWINSZ, &ts);
	col_size = (ts.ts_cols / length->name) + 1;
	if (options->one_line)
	{
		col_size = 1;
		length->name = 0;
	}
	line_size = (files->length / col_size);
	if (line_size == 0)
		line_size = 1;
	//	printf("%d %d\n", col_size, line_size);
	while (i < line_size)
	{
		y = 0;
		while (y < col_size)
		{
			if (i + (y * line_size) < files->length)
			{
				file = ft_array$at(files, i + (y * line_size));
				printf("%-*s", length->name, file->name);
			}
			y++;
		}
		printf("\n");
		i++;
	}
}

void ls$print(t_array *files, t_options *options, t_length *length)
{
	if (options->long_format)
	{
		printf("total %d\n", length->total);
		ft_array$func(files, print_long,
			length);
	}
	else
		ls$print_col(files, length, options);
}
