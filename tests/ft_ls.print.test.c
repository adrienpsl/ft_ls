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
#include <libft.test.h>
#include "ft_ls.h"

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
	mkdir("clean_dir", ACCESSPERMS);
	mkdir("no_access", 0);
	system("touch file_1");
	system("touch file_2");

	system("mkdir -p .hidden");
	system("mkdir -p dir_1");
	system("mkdir -p dir_2");
	system("mkdir -p DIR_1");
	system("mkdir -p DIR_2");
	system("mkdir -p DIR_3");

	system("touch clean_dir/clean_dir_1");
	system("ln -s clean_dir link_dir 2>1 toto");
}

static int utils(char *av_str, char *result)
{
	char **av_split = ft_strsplit(av_str, " ");
	char **av = av_split;
	t_ls ls = { 0 };
	(void)result;

	ls$catch_options(&av, (long *)&ls.options);

	g_test = 1;
	t_array *test_array = build_list(&ls, av);
	g_test = 0;

	ft_array$func(test_array, print_func, NULL);

	ft_array$free(&test_array);
	ft_strsplit_free(&av_split);
	//	if (lib_cmp_testbuff(result))
	//		return (1);

	return (0);
}






void test_ls$print()
{
	init();
	utils(
		" dir_1 dir_2 DIR_2 DIR_1 file_1 . .hidden  file_2 DIR_3  FILE_1 FILE_2",
		"");

	// parcourir le repertoir et lister tout les fichier,
	// a chaque file, mettre le truc pour le trie
	// et update les differente value pour avoir la volue min et max value
	//

}
