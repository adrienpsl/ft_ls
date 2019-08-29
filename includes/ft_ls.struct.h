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

#ifndef FT_LS_FT_LS_STRUCT_H
#define FT_LS_FT_LS_STRUCT_H

#include <sys/stat.h>
#include <dirent.h>
#include "ft_ls.h"

typedef struct s_bf
{
	struct dirent *dp;
	DIR *dir;
	t_array *files;
	char full_path[PATH_MAX + 1];
	char file_name[PATH_MAX + 1];
	t_file file;
	t_options *options;
	t_length *length;
	struct stat fs;
} t_bf;

#endif
