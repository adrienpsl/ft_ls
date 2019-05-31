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
# include "ft_libft.h"

/*
**	includes
*/
# include <sys/param.h>
# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>


/*
**    project includes
*/
# include "struct.h"

# define FT_ISBLK(m)  (((m) & (unsigned int)S_IFMT) == S_IFBLK)
# define FT_ISCHR(m)  (((m) & (unsigned int)S_IFMT) == S_IFCHR)
# define FT_ISDIR(m)  (((m) & (unsigned int)S_IFMT) == S_IFDIR)
# define FT_ISFIFO(m) (((m) & (unsigned int)S_IFMT) == S_IFIFO)
# define FT_ISLNK(m)  (((m) & (unsigned int)S_IFMT) == S_IFLNK)
# define FT_ISSOCK(m) (((m) & (unsigned int)S_IFMT) == S_IFSOCK)

#define HARD_LINK_SIZE 0
#define UID_SIZE 1
#define GUID_SIZE 2
#define SIZE_SIZE 3

# define FILE_NAME_MAX_SIZE 255

typedef struct		s_ls
{
	long options;
	char *start_name;
	int size_coll[4];
	char path[PATH_MAX + 1];
	long total;
	// ici je met le tab a clean
	// et la size de mes elements
}					t_ls;


typedef struct		s_ls_link
{
	int name_size;
	int hard_link;
	char *guid;
	char *uid;
	long mtime;
	unsigned long long size;
	char file_mode[11];
	char name[FILE_NAME_MAX_SIZE];
	char sym_real[FILE_NAME_MAX_SIZE];
}					t_ls_link;

/*
**	option
*/
# define FT_LS_RECURSION	1
# define FT_LS_LONG			(1 << 1)
# define FT_LS_ALL			(1 << 2)
# define FT_LS_REVERSE		(1 << 3)
# define FT_LS_TIME			(1 << 4)


/*
**	functions
*/
char *get_time(long int *time, int mode, char *out);
void ft_get_permission(const mode_t *st_mode, char *fileMode);
int ft_fill_link(char *path, t_ls_link *link, t_ls *ls);
void ft_ls_sort(t_ls *ls, t_array *array, int nb_elements);


#endif
