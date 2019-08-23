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
#define LSTAT 2


# define LS_OPTIONS "aRl"

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
	unsigned long sort_time: 1; //
	unsigned long sort_last_access: 1; // u
	unsigned long sort_size: 1; // S
	unsigned long sort_status_change: 1; // c
	unsigned long av_mode: 1;

} t_ls_options;

typedef struct t_length {
	int uid;
	int gid;
	int size;
	int hard_link;
	int name;
} t_length;

typedef struct s_ls
{
	t_length length;
	t_ls_options options;
	t_buffer buffer;
	t_array *dirs;
	int reverse_sorting;
} t_ls;



t_file *
fill_file_element(char *full_path, char *file_name, t_ls_options *options,
	t_length *length);

/*
**	print element
*/
void add_hardlink_size(t_file *file, struct stat *fs);
void add_uid_gid(t_file *file, struct stat *fs);
void add_file_and_link_name(t_file *file, char *file_name, char *full_path,
	struct stat *fs);
void add_right(char *buff, const mode_t mode);
void add_type(t_file *file, const mode_t mode);
int add_acl_extended(char *buff, char *path);
void add_time(long int time_nb, char *buffer, t_ls_options *options);
void add_max_length(t_file *file, t_length *length);
void
add_sort_param(t_file *file, struct stat *fs, t_ls_options *options);
char *build_full_path(char *dir_path, char *name);

/*
**	utils
*/
int print_link(void *p_link, void *n);
struct stat *get_stat(char *path, int mode);

int print_func(void *p_element, void *p_param);

t_array *build_list(t_ls_options *options, char **av, t_length *length);

/*
**	--- parsing ----------------------------------------------------------------
*/
int ls_parsing$sort_func(void *a, void *b, void *param);
int ls_parsing$first_dir_func(void *p_el, void *param);

int ls_array$sort_func(void *a, void *b, void *p_param);

int ls$catch_options(char ***p_av, t_ls_options *option);

void add_file_attribute(char *buff, char *path, mode_t mode);
t_array *build_dir_array(char *dir_path, t_ls_options *options);

void test_ft_ls$main_test();
int line_print(void *p_el, void *param);

/*
**	test delete
*/
int print_link_test(void *p_link, void *n);

#endif
