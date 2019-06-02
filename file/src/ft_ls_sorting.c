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

void swap_func(void *a, void *b)
{
	t_file tmp;
	ft_mem_copy(&tmp, a, sizeof(t_file));
	ft_mem_copy(a, b, sizeof(t_file));
	ft_mem_copy(b, &tmp, sizeof(t_file));
}

int sort_func(void *p_l1, void *p_l2, void *p_param)
{
	t_file *l1;
	t_file *l2;
	long param;
	int ret;

	param = *(long *) p_param;
	l1 = p_l1;
	l2 = p_l2;

	// si t return by t
//	if (param & FT_LS_TIME)
//		return 1;
//	else
	ret =  ft_mem_cmp(l1->name, l2->name, FT_LS_MAX_FILE) >= 0 ? 0 : 1;

	return  param & FT_LS_REVERSE ? !ret : ret;
}

int ft_ls_sort(t_ls *l)
{
	t_quick quick;

	quick.swap_func = swap_func;
	quick.array = l->array;
	quick.param = &l->options;
	quick.cmp_func = sort_func;
	ft_quick_sort(&quick, 0, l->nb_elements - 1);
	return (0);
}