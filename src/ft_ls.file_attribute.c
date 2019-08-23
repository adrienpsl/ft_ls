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

#include "ft_ls..h"
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/xattr.h>

void add_type(char *buff, const mode_t mode)
{
	static int filters[7] = { S_IFBLK, S_IFCHR, S_IFIFO, S_IFDIR,
							  S_IFLNK, S_IFSOCK, S_IFREG };
	static char char_type[] = "bcpdls-";
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
			*buff = char_type[i];
			break;
		}
		i++;
	}
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
		if (i == 3 && (mode & S_ISUID))
			buff[i] = buff[i] == 'x' ? 's' : 'S';
		else if (i == 6 && (mode & S_ISGID))
			buff[i] = buff[i] == 'x' ? 's' : 'S';
		else if (i == 8 && (mode & S_ISVTX))
			buff[i] = buff[i] == 'x' ? 't' : 'T';
		i++;
	}
}

int add_acl_extended(char *buff, char *path)
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
	buff[1] = ' ';
	return (0);
}
