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
# define FT_LS_FT_LS_STRUCT_H

# include <sys/stat.h>
# include <dirent.h>
# include <stdint.h>
# include <limits.h>
# include <ft_array.h>
# include "ft_ls.h"

typedef struct		s_ls_options
{
	unsigned long	all: 1;
	unsigned long	recursif: 1;
	unsigned long	long_format: 1;
	unsigned long	reverse: 1;
	unsigned long	sort_time: 1;
	unsigned long	sort_last_access: 1;
	unsigned long	sort_size: 1;
	unsigned long	sort_status_change: 1;
	unsigned long	one_line: 1;
	unsigned long	big_time: 1;
	unsigned long	numeric_group: 1;
	unsigned long	no_group: 1;
	unsigned long	print_path: 2;
}					t_options;

typedef struct		s_file
{
	char			type[16];
	char			uid[30];
	char			gid[30];
	char			size[64];
	char			time[32];
	char			hardlink_nb[64];
	char			name[__DARWIN_MAXPATHLEN + 1];
	char			link[__DARWIN_MAXPATHLEN + 1];
	long			sort_data;
	uintmax_t		time_nb;
}					t_file;

typedef struct		s_length
{
	int				uid;
	int				gid;
	int				size;
	int				hard_link;
	int				name;
	int				total;
	int				is_driver;
}					t_length;

typedef struct		s_ls
{
	t_length		length;
	t_options		options;
	t_file			*dir;
	t_array			*av_directories;
	t_array			*av_files;
}					t_ls;

typedef struct		s_bf
{
	struct dirent	*dp;
	DIR				*dir;
	t_array			*files;
	char			full_path[PATH_MAX + 1];
	char			file_name[PATH_MAX + 1];
	t_file			file;
	t_options		*options;
	t_length		*length;
	struct stat		fs;
}					t_bf;

#endif
