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

# include "ft_ls..h"
# include "string.h"
# include "../src/ft_ls.generate_files_array.c"

int ls_parsing$sort_func(void *a, void *b, void *param)
{
	(void)param;
	t_file *f_1;
	t_file *f_2;

	f_1 = a;
	f_2 = b;

	if (f_1->is_dir == f_2->is_dir)
	{
		return (ft_str_cmp(f_1->name, f_2->name) > 0);
	}
	else
		return (f_1->is_dir < f_2->is_dir ? 0 : 1);
}

static void
fill_array_with_argv(char **av, t_options *options, t_array **array,
	t_length *length)
{
	t_file *file;

	options->is_argv = 1;
	while (NULL != *av)
	{
		if (
			*av && ft_strlen(*av) >= 255
			)
			ft_dprintf(2, "ls: %s: file name too long ( >= 255 )\n", *av,
					   strerror(errno));
		else if (
			(file = fill_file_element(*av, *av, options, length))
			)
			ft_array$push(array, file);
		else
			ft_printf("ls: %s: %s\n", *av, strerror(errno));
		av++;
	}
	options->is_argv = 0;
}

/**
 * @brief 	cette fonction va fill le dir array et le fil array de ls
 * av mode used set lstat or stat for the file stat
 * @param ls
 * @param av
 * @return
 */


t_array *ls$build_av_array(t_options *options, char **av, t_length *length)
{
	static char *no_argv[2] = { "." };
	t_array *dirs;

	if (
		!options->long_format
		)
		options->av_mode = 1;
	if (
		NULL == (dirs = ft_array$init(50, sizeof(t_file)))
		)
		return (NULL);
	{
		if (*av)
			fill_array_with_argv(av, options, &dirs, length);
		else
			fill_array_with_argv(no_argv, options, &dirs, length);
	}
	ft_array$sort_bubble(dirs, ls_parsing$sort_func, NULL);
	options->av_mode = 0;
	return (dirs);
}