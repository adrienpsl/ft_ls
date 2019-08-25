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
#include <sys/stat.h>
# include "libft.h"

#define STAT  1

typedef struct s_file
{
	char type[16];
	int is_dir;
	char uid[30];
	char gid[30];
	char size[64];
	char time[32];
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
	unsigned long reverse: 1;
	unsigned long sort_time: 1; // t
	unsigned long sort_last_access: 1; // u
	unsigned long sort_size: 1; // S
	unsigned long sort_status_change: 1; // c
	unsigned long one_line: 1; // 1
	unsigned long av_mode: 1;
	unsigned long custom_sort: 1;
	unsigned long is_first: 1;
} t_options;

# define LS_OPTIONS "aRlrtuSc1"

typedef struct t_length
{
	int uid;
	int gid;
	int size;
	int hard_link;
	int name;
	int total;
} t_length;

typedef struct s_ls
{
	t_length length;
	t_options options;
} t_ls;

int ft_ls(char **av);

/*
**	print element
*/
void add_time(long int time_nb, char *buffer, t_options *options);
void
add_sort_param(t_file *file, struct stat *fs, t_options *options);
void
ls$print(t_array *files, t_options *options, t_length *length, int print_total);

/*
**	utils
*/
struct stat *get_stat(char *path, int mode);
void **generate_arr_ptr(t_options *options, t_length *length);

t_array *ls$build_av_array(t_options *options, char **av, t_length *length);

int ls$handle_files_array(char *path, t_file *file, t_options *options);

/*
**	--- parsing ----------------------------------------------------------------
*/
int ls_parsing$sort_func(void *a, void *b, void *param);
int ls_parsing$first_dir_func(void *p_el, void *param);

int ls$catch_options(char ***p_av, t_options *option);

t_array *
ls$generate_files_array(char *dir_path, t_options *options, t_length *length);

void test_ft_ls$main_test();

void
ls$add_type_right_acl_hardlink(t_file *file, struct stat *fs, char *full_path);

void
ls$add_size_uid$guid_name_link(t_file *file, struct stat *fs, char *full_path,
	char *file_name);

void
ls$add_sort$param_time_max$length(t_file *file, struct stat *fs,
	t_options *options, t_length *length);

#endif
