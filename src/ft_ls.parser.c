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

# include "ft_ls.h"
# include "string.h"
# include "ft_ls.build_files.c"

void fill_array_with_argv(char **av, t_bf *bf)
{
	while (NULL != *av)
	{
		if (
			*av && ft_strlen(*av) >= 255
			)
		{
			ft_dprintf(2, "ls: %s: file name too long ( >= 255 )\n", *av,
					   strerror(errno));
			continue;
		}
		add_path_name(bf, NULL, *av);
		if (
			OK == fill_file(bf, AV_INPUT)
			)
			ftarray__push(bf->files, &bf->file);
		else
			ft_printf("ls: %s: %s\n", *av, strerror(errno));
		av++;
	}
}

t_array *ls__build_av_files(char **av, t_options *options, t_length *length)
{
	static char *no_argv[2] = { "." };
	static t_bf bf;

	init_bf(&bf, options, length);
	if (
		NULL == (bf.files = ftarray__init(50, sizeof(t_file)))
		)
		return (NULL);
	{
		if (*av)
			fill_array_with_argv(av, &bf);
		else
			fill_array_with_argv(no_argv, &bf);
	}
	ftarray__sort_bubble(bf.files, ls__files_sort_func, options);
	return (bf.files);
}