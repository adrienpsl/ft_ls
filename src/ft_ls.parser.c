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
# include "ft_ls.build_files.c"

// finalement je garde la meme fonction pour tout, mais je mets
// pas tout au meme endroit ?

int ls_parsing_sort_func(void *a, void *b, void *param)
{
	t_file *f_1;
	t_file *f_2;
	t_options *options;

	f_1 = a;
	f_2 = b;
	options = param;

	if (f_1->is_dir == f_2->is_dir)
	{
		if (options->reverse)
		{
			return (!(ft_str_cmp(f_1->name, f_2->name) > 0));
		}
		else
		{
			return ((ft_str_cmp(f_1->name, f_2->name) > 0));
		}
	}
	else
		return (f_1->is_dir < f_2->is_dir ? 0 : 1);
}

void fill_array_with_argv(char **av, t_bf *bf)
{
	while (NULL != *av)
	{
		if (
			*av && ft_strlen(*av) >= 255
			)
			ft_dprintf(2, "ls: %s: file name too long ( >= 255 )\n", *av,
					   strerror(errno));
		else if (
			ERROR == fill_file(bf, AV_INPUT)
			)
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
	//	ft_array$sort_bubble(dirs, ls_parsing$sort_func, options);
	return (bf.files);
}