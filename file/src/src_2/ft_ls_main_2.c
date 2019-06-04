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

/*
 * init and malloc an array to handle the file
 * */
int ft_ls_init(char *path, t_ls_2 *l)
{
	ft_mem_copy(l->path, path, STRING_MODE);
	if (ft_api_dir(l))
		return (-1);
	while (readdir(l->dir))
		l->elements++;
	closedir(l->dir);
	if (ft_array_new(&l->array, l->elements, sizeof(t_file)))
		return (-1);
	ft_str_len(&l->end_path, path);

	return (0);
}

void ft_ls_free(t_ls_2 *l)
{
	if (l->array)
		ft_array_free(&l->array);
	if (l->buff)
		ft_buffer_free(&l->buff);
	memset(l, 0, sizeof(t_ls_2));
}
