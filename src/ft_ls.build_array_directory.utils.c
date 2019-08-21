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

int ls_array$sort_func(void *a, void *b, void *p_param)
{
	t_file *f_1;
	t_file *f_2;
	int ret;
	int *param;

	f_1 = a;
	f_2 = b;
	param = p_param;

	if (f_1->sort_data != f_2->sort_data)
		ret = f_1->sort_data < f_1->sort_data;
	else
		ret = ft_str_cmp(f_1->name, f_2->name) > 0;
	return (*param ? !ret : ret);
}

