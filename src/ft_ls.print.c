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
	t_options *options;

	file = p_element;
	options = p_param;

	// arriver la j'ai le juste le path, et je vais a partir de la print mon element,
	// pour le mement je vais juste print les noms.
	ft_printf("%s", file->name);

	return (0);
}

void print_long_formant(t_file *file, t_length *length)
{
	printf("%s ", file->type);
	printf("%*s ", length->hard_link, file->hardlink_nb);
	printf("%-*s  ", length->uid, file->uid);
	printf("%-*s  ", length->gid, file->gid);
	printf("%*s ", length->size, file->size);
	printf("%s ", file->time);
	printf("%s", file->name);
	if (file->link[0])
		printf(" -> %s", file->link);
	printf("\n");
}

int ls$print_array(void *p_el, void *param)
{
	t_file *file;
	t_length *length;
	t_options *options;

	options = ((void **)param)[0];
	length = ((void **)param)[1];
	file = p_el;
	if (
		!options->all && file->name[0] == '.'
		)
		return (0);

	if (
		options->long_format
		)
		print_long_formant(file, length);
	else
		(void)1;
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
