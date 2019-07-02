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

void ft_swap_file(void *a, void *b)
{
	t_file tmp;

	ft_mem_copy(&tmp, a, sizeof(t_file));
	ft_mem_copy(a, b, sizeof(t_file));
	ft_mem_copy(b, &tmp, sizeof(t_file));
}

int ft_cmp_char(void *a, void *b, void *p_param)
{
	long param;
	int ret;
	t_file *aa;
	t_file *bb;


	(void) param;
	param = *(long *) p_param;
	aa = a;
	bb = b;

	if (aa->dir > bb->dir)
		return 1;
	ret = ft_mem_cmp(aa->argv, bb->argv, STRING_MODE) > 0 ? 1 : 0;
	return param & FT_LS_O_r ? !ret : ret;
}

int ft_cmp_file(void *p_l1, void *p_l2, void *p_param)
{
	t_file *l1;
	t_file *l2;
	long param;
	int ret;

	param = *(long *) p_param;
	l1 = p_l1;
	l2 = p_l2;

	if (param & FT_LS_CUSTOM_SORT)
	{
		if (l1->sort_data == l2->sort_data)
			ret = ft_mem_cmp(l1->name, l2->name, FT_LS_MAX_FILE) > 0 ? 1 : 0;
		else
			ret = (l1->sort_data > l2->sort_data) ? 0 : 1;
	}
	else
		ret = ft_mem_cmp(l1->name, l2->name, FT_LS_MAX_FILE) > 0 ? 1 : 0;
	return param & FT_LS_O_r ? !ret : ret;
}

int ft_ls_sort(t_ls *l)
{
	t_sort quick;

	quick.swap_func = ft_swap_file;
	quick.array = l->array;
	quick.param = &l->options;
	quick.cmp_func = ft_cmp_file;
	ft_quick_sort(&quick, 0, l->elements - 1);
//	ft_array_bubble(&quick);
	return (0);
}