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

#ifndef LS_PROTOTYPES_H
# define LS_PROTOTYPES_H

# include <ft_array.h>
# include "ft_ls.struct.h"

void	add_time(long int time_nb, char *buffer, t_options *options);
void	add_sort_param(t_file *file, struct stat *fs, t_options *options);
void	ls__print(
	t_array *files, t_options *options, t_length *length, int print_total);
t_array	*ls__build_av_files(char **av, t_options *options, t_length *length);
int		ls__loop_on_files(char *path, t_file *file, t_options *options);
int		ls__catch_options(char ***p_av, t_options *option);
t_array	*ls__build_files(
	char *dir_path, t_options *options, t_length *length);
int		ft_ls(char **av);

#endif
