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
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ttycom.h>
# include <sys/ioctl.h>


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

#define FT_LS_HL 0
#define FT_LS_UID 1
#define FT_LS_GUID 2
#define FT_LS_FILE 3
#define FT_LS_DRIVER 4
#define FT_LS_NAME 5

# define FT_LS_MAX_FILE 255

typedef struct s_ls
{
	int nb_elements;
	struct stat fs;
	DIR *dir;
	long options;
	int size_coll[6];
	long total;
	char path[PATH_MAX + 1];
	t_buff *buff;
	t_array *array;
} t_ls;

typedef struct s_ls_2
{
	int elements;
	long options;
	size_t end_path;
	int size[6];
	long total;
	char path[PATH_MAX + 1];
	struct stat fs;
	DIR *dir;
	t_buff *buff;
	t_array *array;
} t_ls_2;

# define FT_LS_DRIVER_MIN 0
# define FT_LS_DRIVER_MAX 1


typedef struct s_ls_link
{
	int hard_link;
	int acl;
	int attr;
	int driver[2];
	char *guid;
	char *uid;
	long mtime;
	size_t name_size;
	unsigned long long size;
	char file_mode[11];
	char name[FT_LS_MAX_FILE];
	char sym_real_file[FT_LS_MAX_FILE];
} t_file;

/*
**	option
*/
# define FT_LS_RECURSION    1
# define FT_LS_LONG            (1 << 1)
# define FT_LS_ALL            (1 << 2)
# define FT_LS_REVERSE        (1 << 3)
# define FT_LS_TIME            (1 << 4)


/*
**	functions
*/
char *get_time(long int *time, int mode, char *out);
int extract_lstat(struct stat *fs, t_file *f, t_ls *ls);
int ft_ls_sort(t_ls *l);
int init_t_ls(char *path, t_ls *l);
int buffer_tab(t_ls *ls);
int is_directory(char *path);


/*
**	helpers
*/
int ft_api_lstat(t_ls_2 *l);
int ft_api_dir(t_ls_2 *l);
#endif
