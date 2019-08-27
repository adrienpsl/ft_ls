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

#ifndef FT_LS_FT_LS_BUILD_FILES_H
#define FT_LS_FT_LS_BUILD_FILES_H

#include "ft_ls..h"
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
# include <sys/stat.h>

# define AV_INPUT 1
# define READDIR_INPUT 0

typedef struct s_bf
{
	struct dirent *dp;
	DIR *dir;
	t_array *files;
	t_file *file;
	char full_path[PATH_MAX + 1];
	char file_name[PATH_MAX + 1];
	t_options *options;
	t_length *length;
	struct stat *fs;
} t_bf;

/*
**	inter function
*/

void add_type(t_file *file, const mode_t mode, t_length *length);
void add_right(char *buff, const mode_t mode);
void add_acl_extended_attribut(char *buff, char *path);
void add_nb_hard_link(t_file *file, struct stat *fs);
void add_size_or_drivers(t_file *file, struct stat *fs);
void add_uid_gid(t_file *file, struct stat *fs);
void add_link_name(t_file *file, struct stat *fs, char *full_path);
void add_total_size(t_bf *bf);
void add_max_length(t_file *file, t_length *length, int source);
void add_sort_param(t_file *file, struct stat *fs, t_options *options);
void add_time(long int time_nb, char *buffer, t_options *options);

/*
**	utils
*/
void init_bf(t_bf *bf, t_options *options, t_length *length);

#endif