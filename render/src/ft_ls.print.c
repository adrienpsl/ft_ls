

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
#include "ft_ls.h"

static int	print_long(void *el, void *param)
{
	t_file		*file;
	t_length	*length;

	file = el;
	length = param;
	ft_printf("%s ", file->type);
	ft_printf("%*s ", length->hard_link, file->hardlink_nb);
	ft_printf("%-*s  ", length->uid, file->uid);
	ft_printf("%-*s  ", length->gid, file->gid);
	if (length->is_driver)
		ft_printf("%8s ", file->size);
	else
		ft_printf("%*s ", length->size, file->size);
	ft_printf("%s ", file->time);
	ft_printf("%s", file->name);
	if (file->link[0])
		ft_printf(" -> %s", file->link);
	ft_printf("\n");
	return (0);
}

void		loop(int line_size, int col_size, t_array *files, t_length *length)
{
	t_file	*file;
	int		i;
	int		y;

	i = 0;
	while (i < line_size)
	{
		y = 0;
		while (y < col_size)
		{
			if (i + (y * line_size) <= files->length)
			{
				file = ftarray__at(files, i + (y * line_size));
				ft_printf("%-*s", length->name, file->name);
			}
			y++;
		}
		ft_printf("\n");
		i++;
	}
}

void		ls_print_col(t_array *files, t_length *length, t_options *options)
{
	struct ttysize	ts;
	int				col_size;
	int				line_size;

	ioctl(0, TIOCGWINSZ, &ts);
	if (length->name == 0)
		return ;
	length->name++;
	col_size = (ts.ts_cols / length->name);
	col_size == 0 ? col_size = 1 : 0;
	if (options->one_line)
	{
		col_size = 1;
		length->name = 0;
	}
	line_size = (files->length / col_size) + 1;
	if (line_size == 0)
		line_size = 1;
	loop(line_size, col_size, files, length);
}

void		ls__print(
	t_array *files, t_options *options, t_length *length, int print_total)
{
	if (options->long_format)
	{
		if (print_total && files->length)
			ft_printf("total %d\n", length->total);
		ftarray__func(files, print_long,
			length);
	}
	else
		ls_print_col(files, length, options);
}
