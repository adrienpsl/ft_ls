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

void ft_ls_get_permission(const mode_t mode, char *file)
{
	static const char rights[] = "rwxrwxrwx";
	static int filters[7] = {S_IFBLK, S_IFCHR, S_IFIFO, S_IFDIR,
							 S_IFLNK, S_IFSOCK, S_IFREG};
	static char char_type[] = "bcpdls-";
	ssize_t i;

	i = -1;
	while (++i < 9)
	{
		file[i + 1] = (mode & (1 << (8 - i))) ? rights[i] : '-';
		if (i == 3 && (mode & S_ISUID))
			file[i] = file[i] == 'x' ? 's' : 'S';
		if (i == 6 && (mode & S_ISGID))
			file[i] = file[i] == 'x' ? 's' : 'S';
		if (i == 8 && (mode & S_ISVTX))
			file[i + 1] = file[i + 1] == 'x' ? 't' : 'T';
	}
	i = -1;
	while (++i < 7)
	{
		if ((S_IFMT & mode) == filters[i])
		{
			file[0] = char_type[i];
			break;
		}
	}
}

int ft_get_acl_extended(char *path, char *buff)
{
	acl_t acl;

	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (listxattr(path, NULL, 0, 0) > 0)
		*buff = '@';
	else if (acl > 0)
	{
		*buff = '+';
		acl_free((void *) acl);
	}
	else
		*buff = ' ';
	return (0);
}

int print_time(long int time_nb, char *out, long option)
{
	long int current_date;
	int active_year;
	int ret;

	ret = 12;
	active_year = 0;
	current_date = time(NULL);
	if (current_date + 3600 <= time_nb)
		active_year = 1;
	if (current_date - 15778800 >= time_nb)
		active_year = 1;

	ft_mem_copy(out, ctime(&time_nb) + 4, 12);
	if (active_year)
		ft_mem_copy(out + 7, ctime(&time_nb) + 19, 5);
	if ((option & FT_LS_O_T) /*&& active_year*/)
	{
		ft_mem_copy(out, ctime(&time_nb) + 4, 20);
		ret = 20;
	}
	return ret;
}


void print_col(t_ls *l, int line_size)
{
	l->f = ft_array_el(l->array, l->i + (l->y * line_size));
	if (l->options & FT_LS_O_1)
		ft_sprintf(l->buff, "%s\n", l->f->name);
	else
		ft_sprintf(l->buff, "%-*s",
				   l->size[FT_LS___NAME] + 1, l->f->name);
}

int print_all_col(t_ls *l)
{
	struct ttysize ts;
	int col_size;
	int line_size;

	ioctl(0, TIOCGWINSZ, &ts);
	l->i = -1;
	l->array->i = 0;
	col_size = ts.ts_cols / (l->size[FT_LS___NAME] + 1);
	col_size <= 0 ? col_size = 1 : 0;
	line_size = (l->elements / col_size) + 1;
	if (l->options & FT_LS_O_1)
		while (++l->i < l->elements)
			print_col(l, l->i);
	else
		while (++l->i < line_size)
		{
			l->y = -1;
			while (++l->y < col_size)
			{
				if (l->i + (l->y * line_size) < l->elements)
					print_col(l, line_size);
			}
			ft_buffer_add(l->buff, "\n", 1);
		}
	return 0;
}

int print_all(t_ls *l)
{
	static int is_first = 1;

	if (((l->options & FT_LS_O_R) && !is_first) || (l->options & FT_LS_O_M))
	{
		if (!is_first)
			ft_buffer_add(l->buff, "\n", 1);
		ft_buffer_add(l->buff, l->path, l->end_path - 1);
		ft_buffer_add(l->buff, ":", 1);
		ft_buffer_add(l->buff, "\n", 1);
	}
	is_first = 0;
	if (l->options & FT_LS_O_l)
	{
		ft_sprintf(l->buff, "total %ld\n", l->total);
		while ((l->f = (t_file *) ft_array_next_el(l->array)))
		{
			if (!*l->f->name)
				continue;
			ft_str_len(&l->s, l->path);
			ft_mem_copy(l->path + l->end_path, l->f->name, STRING_MODE);
			if (ft_api_lstat(l))
				continue;
			print_stats(l);
		}
	}
	else
		print_all_col(l);
	return (0);
}
