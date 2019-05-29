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

#ifndef LEM_IN_ALL_INCLUDES_H
# define LEM_IN_ALL_INCLUDES_H

/*
**    LIBFT
*/
#include <sys/param.h>
# include "ft_libft_header.h"

/*
**    project includes
*/
# include "struct.h"

typedef struct		s_ls
{
	long long options;
	char *start_name;
}					ts_ls;



typedef struct		s_ls_link
{
	char write;
	int name_size;
	int hard_link;
	int uid;
	int guid;
	long mtime;
	unsigned long long size;
	char file_mode[10];
	int size_coll[7];
	char name[MAXPATHLEN];
}					ts_ls_link;



#endif
