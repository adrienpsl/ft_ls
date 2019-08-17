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

# include "libft.h"


# define LS_OPTIONS "aRl"

typedef struct s_file
{
	int dir;
	long sort_data;
	char *argv;
	char *name;
} t_file;

typedef struct s_ls_options
{
	unsigned long all: 1;
	unsigned long recursif: 1;
	unsigned long long_format: 1;

} t_ls_options;

typedef struct s_ls
{
	t_ls_options options;
} t_ls;


int ls$catch_options(char ***p_av, long *option);


void test_ft_ls$main_test();

#endif
