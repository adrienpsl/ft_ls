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

#include <sys/stat.h>
#include "ft_ls..h"


// test with all file type, if there are good print of each of them

// test with file type and cmp with the true ls for all file


void test_right()
{
	mkdir("test_right", ACCESSPERMS);
	chdir("test_rigth");

	// create the file right test
	{
		// test classic right
		system("touch f_000 f_111 f_222 f_666 f_777");
		system("chmod 000 f_000");
		system("chmod 111 f_111");
		system("chmod 222 f_222");
		system("chmod 666 f_666");
		system("chmod 777 f_777");

		// test with the

	}
}

void test_ls$get_dir_array()
{
	t_ls ls;
	t_array *array = build_dir_array("/Users/adpusel/test_ls", &ls.options);
	ls.reverse_sorting = 0;

	ft_array$sort_bubble(array, ls_array$sort_func, &ls.reverse_sorting);
	ft_array$func(array, line_print, &ls.length);

	// faire un script with les

	// test la list directory avec:
}




