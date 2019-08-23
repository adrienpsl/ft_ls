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

static void
fill_array_with_argv(char **av, t_ls_options *options, t_array **array,
	t_length *length)
{
	t_file *file;

	while (NULL != *av)
	{
		if (
			(file = fill_file_element(*av, *av, options, length))
			)
			ft_array$push(array, file);
		else
			ft_dprintf(2, "ls: %s: %s\n", *av, strerror(errno));
		av++;
	}
}

/**
 * @brief 	cette fonction va fill le dir array et le fil array de ls
 *
 * @param ls
 * @param av
 * @return
 */


t_array *ls$build_av_array(t_ls_options *options, char **av, t_length *length)
{
	static char *no_argv[2] = { "." };
	t_array *dir_array;

	if (
		!options->long_format
		)
		options->av_mode = 1;
	if (
		NULL == (dir_array = ft_array$init(50, sizeof(t_file)))
		)
		return (NULL);
	{
		if (*av)
			fill_array_with_argv(av, options, &dir_array, length);
		else
			fill_array_with_argv(no_argv, options, &dir_array, length);
	}
	ft_array$sort_bubble(dir_array, ls_parsing$sort_func, NULL);
	options->av_mode = 0;
	return (dir_array);
}

