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

#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include <sys/dirent.h>
# include "libft.h"

# define LS_OPTIONS "aRl"

typedef struct s_file
{
	char type[16];
	int is_dir;
	char uid[30];
	char gid[30];
	char size[64];
	char hardlink_nb[64];
	char name[__DARWIN_MAXPATHLEN + 1];
	char link[__DARWIN_MAXPATHLEN + 1];
	long sort_data;
} t_file;

typedef struct s_ls_options
{
	unsigned long all: 1;
	unsigned long recursif: 1;
	unsigned long long_format: 1;
} t_ls_options;

typedef struct t_length {
	int uid;
	int gid;
	int size;
	int hard_link;
} t_length;

typedef struct s_ls
{
	t_length length;
	t_ls_options options;
	t_buffer buffer;
} t_ls;

/*
**	utils
*/
int print_link(void *p_link, void *n);

int print_func(void *p_element, void *p_param);

t_array *build_list(t_ls *ls, char **av);

/*
**	--- parsing ----------------------------------------------------------------
*/
int ls_parsing$sort_func(void *a, void *b, void *param);
int ls_parsing$first_dir_func(void *p_el, void *param);

int ls$catch_options(char ***p_av, long *option);

void ls$get_file_information(char *buff, char *path, mode_t mode);

void test_ft_ls$main_test();

#endif
