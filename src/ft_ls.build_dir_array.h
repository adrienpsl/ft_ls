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

#ifndef FT_LS_FT_LS_BUILD_DIR_ARRAY_H
#define FT_LS_FT_LS_BUILD_DIR_ARRAY_H

#include <sys/stat.h>
#include <ft_ls..h>
#include <dirent.h>

typedef struct s_bda {
	char full_path[2064];
	char *origin_path;
	char *file_name;
	struct stat fs;
	t_file file;
	struct dirent *dp;
	DIR *dir;
	t_array *array;
} t_bda;

/*
**	Intern function
*/
void add_hardlink_size(t_bda *bda);
void add_uid_gid(t_bda *bda);
void add_file_and_link_name(t_bda *bda);
void add_sort_param_and_time(t_bda *bda, t_ls *ls);

#endif
