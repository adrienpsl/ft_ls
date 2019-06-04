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
	if (acl > 0)
	{
		*buff = '+';
		acl_free((void *) acl);
	}
	else if (listxattr(path, NULL, 0, 0) > 0)
		*buff = '@';
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

static void type_size_uid_guid(t_ls_2 *l)
{
	char buff[30];

	ft_ls_get_permission(l->fs.st_mode, buff);
	ft_get_acl_extended(l->path, buff + 10);
	ft_buffer_add(l->buff, buff, 11);
	ft_sprintf(l->buff, " %*d ", l->size[FT_LS_____HL], l->fs.st_nlink);
	if (l->options & FT_LS_O_n)
	{
		ft_sprintf(l->buff, "%-*d", l->size[FT_LS____UID], l->fs.st_uid);
		ft_sprintf(l->buff, "%-*d", l->size[FT_LS___GUID], l->fs.st_gid);
	}
	else
	{
		ft_sprintf(l->buff, "%-*s",
				   l->size[FT_LS____UID], getpwuid(l->fs.st_uid)->pw_name);
		ft_sprintf(l->buff, "  %-*s  ",
				   l->size[FT_LS___GUID], getgrgid(l->fs.st_gid)->gr_name);
	}
}

static void ft_add_time(t_ls_2 *l)
{
	int time_size;
	char buffer[24];

	if (FT_LS_O_u & l->options)
		time_size = print_time(l->fs.st_atimespec.tv_sec, buffer, l->options);
	else if (FT_LS_O_c & l->options)
		time_size = print_time(l->fs.st_ctimespec.tv_sec, buffer, l->options);
	else
		time_size = print_time(l->fs.st_mtimespec.tv_sec, buffer, l->options);
	ft_buffer_add(l->buff, buffer, time_size);
}

static void ft_add_size(t_ls_2 *l)
{
	if (S_ISBLK(l->fs.st_mode) || S_ISCHR(l->fs.st_mode))
	{
		(l->size[FT_LS___FILE] = 4);
		(l->size[FT_LS_DRIVER] = 3);
		ft_sprintf(l->buff, "%*d,",
				   l->size[FT_LS_DRIVER], major(l->fs.st_rdev));
		if (minor(l->fs.st_rdev) > 255)
			ft_sprintf(l->buff, " %0*x ",
					   10, minor(l->fs.st_rdev));
		else
			ft_sprintf(l->buff, "%*d ",
					   l->size[FT_LS___FILE], minor(l->fs.st_rdev));
	}
	else
	{
		if (l->has_driver)
			ft_sprintf(l->buff, "%*ld ",
					   l->size[FT_LS___FILE] + 4, l->fs.st_size);
		else
			ft_sprintf(l->buff, "%*ld ",
					   l->size[FT_LS___FILE], l->fs.st_size);
	}
}

static int name_symlink(t_ls_2 *l, t_file *file)
{
	ft_sprintf(l->buff, " %s", file->name);
	if (FT_ISLNK(l->fs.st_mode))
		ft_sprintf(l->buff, " -> %s", l->link);
	return (0);
}


//// TODO : add l'option -n
//// ici je vais print dans mon buffer, avec le sprintf
//int print_stats_element(t_ls_2 *l, t_file *file)
//{
//	// les droit et types du file
//	// les acl et @
//	// taille
//	// uid et guid //
//	// taille : si c'est le type drivers, ne pas tout print
//	// l'heure : gere si file too old ou too young + option T, je vais faire tt les test en T
//	// name file + if needed symlink
//}

// que print en foncion des options en long
int print_stats(t_ls_2 *l)
{
	t_file *file;
	size_t file_size;

	ft_ls_sort(l);
	while ((file = (t_file *) ft_array_next_el(l->array)))
	{
		if (!*file->name)
			continue;
		ft_str_len(&file_size, l->path);
		ft_mem_copy(l->path + l->end_path, file->name, STRING_MODE);
		if (ft_api_lstat(l))
			continue;
		if (FT_ISLNK(l->fs.st_mode)
			&& readlink(l->path, l->link, FT_LS_MAX_FILE) == -1)
			return (-1);
		type_size_uid_guid(l);
		ft_add_size(l);
		ft_add_time(l);
		name_symlink(l, file);
		ft_buffer_add(l->buff, "\n", 1);
	}
	return (0);
}


// print en col

//