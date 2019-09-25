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
# define FT_LS_FT_LS_BUILD_FILES_H

# include "ft_ls.h"
# include "ft_ls.struct.h"
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/dirent.h>
# include <sys/stat.h>
# include "libft.h"


/*
**	-- add file function
*/
void add_type(t_file *file, const mode_t mode, t_length *length);
void add_right(char *buff, const mode_t mode);
void add_acl_extended_attribut(char *buff, char *path);
void add_nb_hard_link(t_file *file, struct stat *fs);
void add_size_or_drivers(t_file *file, struct stat *fs);
void add_uid_gid(t_file *file, struct stat *fs, t_options *options);
void
add_link_name(t_file *file, struct stat *fs, char *full_path, char *file_name);
void add_total_size(t_bf *bf);
void add_max_length(t_file *file, t_length *length, int source);
void add_sort_param(t_file *file, struct stat *fs, t_options *options);
void add_time(long int time_nb, char *buffer, t_options *options);

/*
**	utils
*/
void init_bf(t_bf *bf, t_options *options, t_length *length);
int add_path_name(t_bf *bf, char *dir_path, char *name);
int ls__files_sort_func(void *a, void *b, void *p_param);

#endif
