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
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>

int print_func(void *p_element, void *p_param)
{
	t_file *file;
	t_ls_options *options;

	file = p_element;
	options = p_param;

	// arriver la j'ai le juste le path, et je vais a partir de la print mon element,
	// pour le mement je vais juste print les noms.
	ft_printf("%s", file->name);

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
