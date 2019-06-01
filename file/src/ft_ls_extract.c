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

char ft_get_type(const mode_t *st_mode_ptr)
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

void ft_get_permission(const mode_t *st_mode, char *fileMode)
{
	fileMode[0] = ft_get_type(st_mode);
	fileMode[1] = *st_mode & (unsigned int) S_IRUSR ? 'r' : '-';
	fileMode[2] = *st_mode & (unsigned int) S_IWUSR ? 'w' : '-';
	fileMode[3] = *st_mode & (unsigned int) S_IXUSR ? 'x' : '-';
	fileMode[4] = *st_mode & (unsigned int) S_IRGRP ? 'r' : '-';
	fileMode[5] = *st_mode & (unsigned int) S_IWGRP ? 'w' : '-';
	fileMode[6] = *st_mode & (unsigned int) S_IXGRP ? 'x' : '-';
	fileMode[7] = *st_mode & (unsigned int) S_IROTH ? 'r' : '-';
	fileMode[8] = *st_mode & (unsigned int) S_IWOTH ? 'w' : '-';
	fileMode[9] = *st_mode & (unsigned int) S_IXOTH ? 'x' : '-';
}

size_t length_itoa(int nb)
{
	static const char *base = "0123456789";
	char buff[30];

	ft_mem_set(&buff, 0, 30);
	ft_itoa_base(nb, base, buff, 0);
	return ft_str_len(buff);
}

void set_max_length(int witch_size, int *size_array, int nb, char *str)
{
	int size;

	if (str)
		size = ft_str_len(str);
	else
		size = length_itoa(nb);
	if (size > size_array[witch_size])
		size_array[witch_size] = size;
}

int ft_fill_line(struct stat *fs, t_file *f, t_ls *ls)
{
	ft_get_permission(&fs->st_mode, f->file_mode);
	ls->total += fs->st_blocks;
	f->hard_link = fs->st_nlink;
	set_max_length(HARD_LINK_SIZE, ls->size_coll, f->hard_link, NULL);
	f->uid = getpwuid(fs->st_uid)->pw_name;
	set_max_length(UID_SIZE, ls->size_coll, 0, f->uid);
	f->guid = getgrgid(fs->st_gid)->gr_name;
	set_max_length(GUID_SIZE, ls->size_coll, 0, f->guid);
	f->size = fs->st_size;
	set_max_length(SIZE_SIZE, ls->size_coll, f->size, NULL);
	f->mtime = fs->st_mtime;
	if (FT_ISBLK(fs->st_mode) || FT_ISCHR(fs->st_mode))
	{
		f->driver[FT_LS_DRIVER_MAX] = major(fs->st_rdev);
		f->driver[FT_LS_DRIVER_MIN] = minor(fs->st_rdev);
		set_max_length(SIZE_SIZE, ls->size_coll,
					   f->driver[FT_LS_DRIVER_MIN], NULL);
		ls->size_coll[SIZE_SIZE] +=
				(2 + length_itoa(f->driver[FT_LS_DRIVER_MAX]));
		set_max_length(DRIVER_MAX_SIZE, ls->size_coll,
				f->driver[FT_LS_DRIVER_MAX], NULL);
	}
	return (0);
}
