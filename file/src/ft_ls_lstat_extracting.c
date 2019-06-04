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


// TODO : need to get the sticky bit and the setuid/ setguid
/*
 * set uid  :
 * set guid	:
 * set sicky bit.
 * le maj se font avec le bit d'execusion actif ou non,
 *
 *
 * */
static char ft_get_type(const mode_t *st_mode_ptr)
{
	const mode_t st_mode = *st_mode_ptr;
	if (FT_ISBLK(st_mode))
		return 'b';
	if (FT_ISCHR(st_mode))
		return 'c';
	if (FT_ISFIFO(st_mode))
		return 'p';
	if (FT_ISDIR(st_mode))
		return 'd';
	if (FT_ISLNK(st_mode))
		return 'l';
	if (FT_ISSOCK(st_mode))
		return 's';
	else
		return '-';
}

// i need the s and the t at the end
void ft_get_permission(const mode_t mode, char *file_mode)
{
	static const char chars[] = "rwxrwxrwx";
	ssize_t i;

	i = -1;
	while (i++ < 9)
		file_mode[i + 1] = (mode & (1 << (8 - i))) ? chars[i] : '-';
	file_mode[0] = ft_get_type(&mode);


	// ensuite je set les suid, guid, et sticky bit.

	// at the end of the 3 x I need to test if there is the good new test
}

void set_max_length(int witch_size, int *size_array, int nb, char *str)
{
	size_t size;
	static const char *base = "0123456789";
	char buff[30];

	if (str)
		ft_str_len(&size, str);
	else
	{
		ft_mem_set(&buff, 0, 30);
		ft_itoa_base(nb, base, buff, 0);
		ft_str_len(&size, buff);
	}
	if ((int) size > size_array[witch_size])
		size_array[witch_size] = size;
}

int is_directory(char *path)
{
	struct stat fs;
	char type;

	if (lstat(path, &fs))
		return (-1);
	type = ft_get_type(&fs.st_mode);
	return type == 'd' ? 1 : 0;
}

int extract_lstat(struct stat *fs, t_f *f, t_ls *ls)
{
	ft_get_permission(fs->st_mode, f->file_mode);
	f->file_mode[0] = ft_get_type(&fs->st_mode);
	f->hard_link = fs->st_nlink;
	f->uid = getpwuid(fs->st_uid)->pw_name;
	f->guid = getgrgid(fs->st_gid)->gr_name;
	f->size = fs->st_size;
	f->mtime = fs->st_mtime;
	set_max_length(FT_LS_____HL, ls->size_coll, f->hard_link, NULL);
	set_max_length(FT_LS____UID, ls->size_coll, 0, f->uid);
	set_max_length(FT_LS___GUID, ls->size_coll, 0, f->guid);
	set_max_length(FT_LS___FILE, ls->size_coll, f->size, NULL);
	if (FT_ISBLK(fs->st_mode) || FT_ISCHR(fs->st_mode))
	{
		f->driver[FT_LS_DRIVER_MAX] = major(fs->st_rdev);
		f->driver[FT_LS_DRIVER_MIN] = minor(fs->st_rdev);
		set_max_length(FT_LS___FILE, ls->size_coll,
					   f->driver[FT_LS_DRIVER_MIN], NULL);
		set_max_length(FT_LS_DRIVER, ls->size_coll,
					   f->driver[FT_LS_DRIVER_MAX], NULL);
	}
	set_max_length(FT_LS___NAME, ls->size_coll, f->name_size, NULL);
	return (0);
}
