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
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>



int print_func(void *p_element, void *p_param)
{
	t_file *file;
	t_ls_options *options;
	struct stat fs;


	file = p_element;
	options = p_param;

	if (lstat(file->name, &fs))
		(void)1;
//	print_file_type(fs.st_mode);
//	get_rigth(fs.st_mode);
//	get_acl_extended(file->name);



	// arriver la j'ai le juste le path, et je vais a partir de la print mon element,
	// pour le mement je vais juste print les noms.
	printf("%s \n", file->name);

	return (0);
}

//int ls$print(t_array *array, t_ls_options *options)
//{
//	t_file *file;
//
//	while (
//		NULL != (file)
//		)
//	{
//	    ;
//	}
//}
