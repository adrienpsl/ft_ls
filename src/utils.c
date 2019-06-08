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

int ft_api_lstat(t_ls *l)
{
	if (lstat(l->path, &l->fs))
		return (-1);
	return (0);
}

int ft_api_dir(t_ls *l)
{
	// je dois open le link de lstat ? comment faire ?

	if (!(l->dir = opendir(l->path)))
		return (-1);
	return (0);
}

//int is_directory(char *path)
//{
//	struct stat fs;
//	char type;
//
//	if (lstat(path, &fs))
//		return (-1);
//	type = ft_get_type(&fs.st_mode);
//	return type == 'd' ? 1 : 0;
//}


void exit_and_display_error(int ret_function)
{
	if (ret_function)
	{
		perror("exit: ");
		exit(EXIT_FAILURE);
	}
}

DIR *_open_dir(const char *filename)
{
	DIR *ret;

	ret = opendir(filename);
	if (ret == NULL)
		perror("le fichier a ouvrir n'existe pas");
	return (ret);
}
