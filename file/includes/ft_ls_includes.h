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
	int size_coll[4];
}					t_ls;

#define  HARD_LINK_SIZE 0
#define  UID_SIZE 1
#define  GUID_SIZE 2
#define  SIZE_SIZE 3

typedef struct		s_ls_link
{
	char write;
	int name_size;
	int hard_link;
	char *guid;
	char *uid;
	long mtime;
	unsigned long long size;
	char file_mode[11];
	char name[MAXPATHLEN];
}					t_ls_link;



#endif
