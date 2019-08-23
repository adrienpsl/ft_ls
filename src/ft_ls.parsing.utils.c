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

int ls_parsing$sort_func(void *a, void *b, void *param)
{
	(void)param;
	t_file *f_1;
	t_file *f_2;

	f_1 = a;
	f_2 = b;

	if (f_1->is_dir == f_2->is_dir)
	{
		return (ft_str_cmp(f_1->name, f_2->name) > 0);
	}
	else
		return (f_1->is_dir < f_2->is_dir ? 0 : 1);
}

int ls_parsing$first_dir_func(void *p_el, void *param)
{
	(void)param;
	t_file *file;

	file = p_el;

	return (
		file->is_dir
	);
}


