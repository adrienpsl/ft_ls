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

int test_file_type(char *path, t_ft_ls *l)
{
	if (stat(path, &l->ls.fs))
		return (1);
	if (S_ISDIR(l->ls.fs.st_mode))
	{
		l->mode = FT_LS_MODE_DIR;
		ft_str_len(&l->ls.end_path, path);
		ft_mem_copy(l->ls.path, path, l->ls.end_path);
		ft_handle_dir(path, l->options, l->buff, path);
	}
	else
	{
		l->mode = FT_LS_MODE_FILE;
		if (lstat(path, &l->ls.fs))
			return (-1);
		if (l->options & FT_LS_O_l)
		{
			l->ls.f = &l->file;
			l->ls.buff = l->buff;
			ft_mem_copy(l->ls.f->name, path, STRING_MODE);
			print_stats(&l->ls);
		}
		else
			ft_sprintf(l->buff, "%s\n", path);
	}
	return (0);
}

int ft_ls_parse_options(t_ft_ls *l)
{
	int y;
	char *options = "RlartncSguT1";
	int ret;

	while (l->i < l->ac
		   && l->av[l->i][0] == '-')
	{
		if (l->av[l->i][1] == '\0')
			return (l->i++ & 0);
		y = (l->av[l->i][1] == '-') ? 2 : 1;
		if (l->av[l->i][y] == '\0')
			return (l->i++ & 0);
		if ((ret = ft_io_catch_options(l->av[l->i] + y, options, &l->options)))
		{
			ft_printf("ls : illegal option -- ");
			ft_putchar_fd(ret, 1);
			ft_printf("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			return (-1);
		}
		l->i++;
	}
	return (0);
}

int ft_ls_parse_argv(t_ft_ls *l)
{
	char **arr_ptr;

	if (l->i >= l->ac)
		return (0);
	l->has_path = (l->i == l->ac) ? 0 : (l->options |= FT_LS_O_M);
	ft_array_new(&(l->argv), l->ac - l->i, sizeof(char *));
	while (l->i < l->ac)
	{
		arr_ptr = ft_array_next_el(l->argv);
		ft_mem_copy(arr_ptr, l->av[l->i], sizeof(char *));
		l->i++;
	}
	l->sort.array = l->argv;
	ft_array_bubble(&l->sort);
	l->argv->i = 0;
	return (0);
}

int init_ls(t_ft_ls *l, int ac, char **av)
{
	ft_mem_set(l, 0, sizeof(t_ft_ls));
	if (ft_buffer_new(&l->buff, 35000, 1))
		return (-1);
	l->ac = ac;
	l->av = av;
	l->i = 1;
	l->sort.param = &l->options;
	l->sort.swap_func = ft_swap_char;
	l->sort.cmp_func = ft_cmp_char;
	return (0);
}

void all_test();
int main(int ac, char **av)
{
	(void) ac;
	(void) av;
//	all_test();
	t_ft_ls l;
	char **path_p;
//
	init_ls(&l, ac, av);
	ft_ls_parse_options(&l);
	ft_ls_parse_argv(&l);
	if (l.has_path)
		while ((path_p = ft_array_next_el(l.argv)))
			test_file_type((char *) path_p, &l);
	else
		test_file_type(".", &l);
	// TODO : free ls here
	ft_buffer_clean(l.buff);
//	(ft_buffer_clean(l.buff) || ft_buffer_free(&l.buff));
	return 0;
}
