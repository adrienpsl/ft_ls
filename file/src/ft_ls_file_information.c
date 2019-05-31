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
	if (FT_ISDIR(st_mode))
		return 'd';
	if (FT_ISFIFO(st_mode))
		return 'p';
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


void set_max_length(int witch_size, int *size_array, int nb, char *str)
{
	static const char *base = "0123456789";
	int size;
	char buff_nb[30];

	if (str)
		size = ft_str_len(str);
	else
	{
		ft_mem_set(buff_nb, 0, 20);
		ft_itoa_base(nb, base, buff_nb, 0);
		size = ft_str_len(buff_nb);
	}
	if (size > size_array[witch_size])
		size_array[witch_size] = size;
}

int ft_fill_link(char *path, t_ls_link *link, t_ls *ls)
{
	struct stat fileStat;

	lstat(path, &fileStat);
//	nbytes = readlink(argv[1], buf, bufsiz);
//	nbBlock += fileStat.st_blocks;

	ft_get_permission(&fileStat.st_mode, link->file_mode);

	// check le retour
	if (FT_ISLNK(fileStat.st_mode))
		readlink(path, link->sym_real, FILE_NAME_MAX_SIZE);

	link->hard_link = fileStat.st_nlink;
	set_max_length(HARD_LINK_SIZE, ls->size_coll, link->hard_link, NULL);
	link->uid = getpwuid(fileStat.st_uid)->pw_name;
	set_max_length(UID_SIZE, ls->size_coll, 0, link->uid);
	link->guid = getgrgid(fileStat.st_gid)->gr_name;
	set_max_length(GUID_SIZE, ls->size_coll, 0, link->guid);
	link->size = fileStat.st_size;
	set_max_length(SIZE_SIZE, ls->size_coll, link->size, NULL);
	link->mtime = fileStat.st_mtime;
	free(path);
	return (0);
}