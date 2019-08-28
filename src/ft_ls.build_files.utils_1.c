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
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/xattr.h>

void add_type(t_file *file, const mode_t mode, t_length *length)
{
	static int filters[7] = { S_IFBLK, S_IFCHR, S_IFIFO, S_IFDIR,
							  S_IFLNK, S_IFSOCK, S_IFREG };
	static char *char_type = "bcpdls-";
	int i;

	i = 0;
	while (
		i < 7
		)
	{
		if (
			(S_IFMT & mode) == filters[i]
			)
		{
			file->type[0] = char_type[i];
			break;
		}
		i++;
	}
	if (
		file->type[0] == 'b' || file->type[0] == 'c'
		)
		length->is_driver = 1;
}

void add_right(char *buff, const mode_t mode)
{
	static const char *rights = "rwxrwxrwx";
	int i;

	i = 0;
	while (
		i < 9
		)
	{
		buff[i] = (mode & (1 << (8 - i))) ? rights[i] : '-';
		if (i == 2 && (mode & S_ISUID))
			buff[i] = buff[i] == 'x' ? 's' : 'S';
		else if (i == 5 && (mode & S_ISGID))
			buff[i] = buff[i] == 'x' ? 's' : 'S';
		else if (i == 8 && (mode & S_ISVTX))
			buff[i] = buff[i] == 'x' ? 't' : 'T';
		i++;
	}
}

void add_acl_extended_attribut(char *buff, char *path)
{
	acl_t acl;

	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (listxattr(path, NULL, 0, 0) > 0)
		*buff = '@';
	else if (acl > 0)
	{
		*buff = '+';
		acl_free((void *)acl);
	}
	else
		*buff = ' ';
}

void add_nb_hard_link(t_file *file, struct stat *fs)
{
	ft_sprintf(file->hardlink_nb, "%d", fs->st_nlink);
}
