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

// si c'est un -l et un symlink, pas de mode dossier. sinon mode dossier
// ici je regarde si c'set un link et si c'est un dossier. car en fonction
// je ne fais pas le meme chose.

// on va partir du principe que la vitesse c'est pas pour tout de suite

int test_file_type(char *path, t_ft_ls *l)
{
	ft_str_len(&l->ls.end_path, path);
	ft_mem_copy(l->ls.path, path, l->ls.end_path);
	if (!stat(path, &l->ls.fs) && S_ISDIR(l->ls.fs.st_mode))
	{
		if (!lstat(path, &l->ls.fs)
			&& FT_ISLNK(l->ls.fs.st_mode)
			&& (l->options & FT_LS_O_l))
		{
			l->ls.f = &l->file;
			l->ls.buff = l->buff;
			ft_mem_copy(l->ls.f->name, path, STRING_MODE);
			print_stats(&l->ls);
		}
		else
		{
			stat(path, &l->ls.fs);
			l->mode = FT_LS_MODE_DIR;
			ft_handle_dir(path, l->options, l->buff, path);
		}

	}
	else if (!lstat(path, &l->ls.fs))
	{
		l->mode = FT_LS_MODE_FILE;
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
	else
	{
		ft_str_put_fd("ls: ", 2);
		if (path[0] == 0)
			ft_str_put_fd(": ", 2);
		perror(path);
		return (-1);
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
			return (0);
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

// nouveau je fais un type file, et je met les dir dedans,
// ca va me permettre de mieux gere mes erreurs.
// ici fais un stat sur mon fichier, et je le range ici ! hehe :).
int ft_ls_parse_argv(t_ft_ls *l)
{
	t_file *file;

	if (l->i >= l->ac)
		return (0);
	l->has_path = (l->ac - l->i > 1) ? (l->options |= FT_LS_O_M) : 0;
	ft_array_new(&l->argv, l->ac - l->i, sizeof(t_file));
	while (l->i < l->ac)
	{
		file = ft_array_next_el(l->argv);
		file->argv = l->av[l->i];
		if (!stat(file->argv, &l->ls.fs))
			file->dir = S_ISDIR(l->ls.fs.st_mode);
		l->i++;
	}
	l->sort.array = l->argv;
	ft_quick_sort(&l->sort, 0, l->argv->length - 1);
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
	l->sort.swap_func = ft_swap_file;
	l->sort.cmp_func = ft_cmp_char;
	return (0);
}

int main(int ac, char **av)
{
	t_ft_ls l;
	t_file *file;

	if (!init_ls(&l, ac, av)
		&& !ft_ls_parse_options(&l)
		&& !ft_ls_parse_argv(&l))
	{
		if (l.argv)
			while ((file = ft_array_next_el(l.argv)))
				test_file_type(file->argv, &l);
		else
			test_file_type(".", &l);
	}
	ft_buffer_clean(l.buff);
//	free(&l.buff);
	return (0);
}
