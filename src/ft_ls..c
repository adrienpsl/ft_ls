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

#include <ft_ls..h>

void build_dir_list(t_file *file, t_ls *ls)
{
	t_array *array;

	array = build_dir_array(file->name, ls);
}

int ft_ls$(char **av)
{
	t_ls ls;
	void *tmp;

	ls.buffer.fd = 1;
	ft_bzero(&ls, sizeof(ls));
	ls$catch_options(&av, (long *)&ls.options);

	build_list(&ls, av);
	// test if . is get good handling

	while ((tmp = ft_array$next(ls.dirs)))
	{
		build_dir_list(tmp, &ls);
	}
	// je parcours cette list tant que je n'ai pas eu de

	// ici

	return (0);
}

//  if pas argv


