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
#include <test.h>
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

// brw-r-----  1 root     operator    1,   1 Aug 18 04:56 /dev/disk0s1
// 1 root  operator 0 Aug 18 05:01 /dev/disk0s1

static int utils(char *av_str, char *result)
{
	char **av_split = ft_strsplit(av_str, " ");
	char **av = av_split;
	t_ls_options options;
	t_length length;

	ft_bzero(&options, sizeof(t_ls_options));
	ft_bzero(&length, sizeof(t_length));
	(void)result;

	ls$catch_options(&av, &options);

	t_array *test_array = build_list(&options, av, &length);

	ft_array$func(test_array, line_print, &length);

	ft_array$free(&test_array);
	ft_strsplit_free(&av_split);
	if (lib_cmp_testbuff(result))
		return (1);

	return (0);
}

void test_ls$get_dir_array()
{
	// test driver
	(void)utils;
	utils("-l /var/run/mDNSResponder /dev/ttywf /Users/adpusel/code/42/ft_ls/cmake-build-debug/test_dir/fifo /dev/disk0s1 /tmp", "");


	//	t_ls ls;
	//	t_array *array = build_dir_array("/Users/adpusel/test_ls", &ls.options);
	//	ls.reverse_sorting = 0;
	//
	//	ft_array$sort_bubble(array, ls_array$sort_func, &ls.reverse_sorting);
	//	ft_array$func(array, line_print, &ls.length);

	// faire un script with les

	// test la list directory avec:
}




