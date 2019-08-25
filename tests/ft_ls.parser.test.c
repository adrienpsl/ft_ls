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
#include <stdlib.h>
#include <zconf.h>
#include <ft_ls..h>
#include <libft.test.h>
#include <test.h>

/*
 * do a script witch build the stuff
 * 	- no exist
 * 	- exist
 * 	- sym + long
 * 	- no data
 * 	- list
 * */
static void init()
{
	system("mkdir -p test_dir");
	chdir("test_dir");

	system("mkdir -p  parser_dir");
	chdir("parser_dir");

	mkdir("clean_dir", ACCESSPERMS);
	mkdir("no_access", 0);
	system("touch normal_file");
	system("touch file_1");
	system("touch file_2");

	system("mkdir -p .hidden");
	system("mkdir -p dir_1");
	system("mkdir -p dir_2");
	system("mkdir -p DIR_1");
	system("mkdir -p DIR_2");
	system("mkdir -p DIR_3");

	system("touch clean_dir/clean_dir_1");
	system("ln -s clean_dir link_dir 2>1 /dev/random");
}

static int utils(char *av_str, char *result)
{
	char **av_split = ft_strsplit(av_str, " ");
	char **av = av_split;
	t_options options;
	ft_bzero(&options, sizeof(t_options));
	(void)result;

	ls$catch_options(&av, &options);

	t_array *test_array = ls$build_av_array(&options, av, NULL);

//	ft_array$func(test_array, print_link, NULL);

	ft_array$free(&test_array);
	ft_strsplit_free(&av_split);
	if (lib_cmp_testbuff(result))
		return (1);

	return (0);
}

void test_ls$parser()
{
	init();

	g_test = 1;
	lib_clear_testbuff();

	/*
	* test error handling
	* */
	{
		// file not exist
		utils("did_not_exist",
			  "ls: did_not_exist: No such file or directory\n");

		// file no permit
		utils("no_access/toto",
			  "ls: no_access/toto: Permission denied\n");
	}

	/*
	* test all good one argv
	* */
	{
		//		 directory
		utils("no_access", "no_access || 1\n");

		// file
		utils("normal_file", "normal_file || 0\n");

		// symlink
		utils("link_dir", "link_dir || 1\n");

		// symlink with -l
		utils("-l link_dir", "link_dir || 0\n");
	}

	/*
	* test error multiple file
	* */
	{
		utils("aa bb .",
			  "ls: aa: No such file or directory\n"
			  "ls: bb: No such file or directory\n"
			  ". || 1\n");

		utils("aa bb . no_access/toto",
			  "ls: aa: No such file or directory\n"
			  "ls: bb: No such file or directory\n"
			  "ls: no_access/toto: Permission denied\n"
			  ". || 1\n");
	}

	/*
	* test multiple file, need to sort the list
	* */
	utils(
		" dir_1 dir_2 DIR_2 DIR_1 file_1 . .hidden  file_2 DIR_3  FILE_1 FILE_2",
		"FILE_1 || 0\n"
		"FILE_2 || 0\n"
		"file_1 || 0\n"
		"file_2 || 0\n"
		". || 1\n"
		".hidden || 1\n"
		"DIR_1 || 1\n"
		"DIR_2 || 1\n"
		"DIR_3 || 1\n"
		"dir_1 || 1\n"
		"dir_2 || 1\n");



	/*
	* test with no argv
	* */
	utils("", ". || 1\n");



	g_test = 0;
}


