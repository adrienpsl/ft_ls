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

# define FT_STRING_MODE 1

/*
**    project includes
*/
# include "struct.h"

# define FT_ISBLK(m)  (((m) & (unsigned int)S_IFMT) == S_IFBLK)
# define FT_ISCHR(m)  (((m) & (unsigned int)S_IFMT) == S_IFCHR)
# define FT_ISDIR(m)  (((m) & (unsigned int)S_IFMT) == S_IFDIR)
# define FT_ISFIFO(m) (((m) & (unsigned int)S_IFMT) == S_IFIFO)
# define FT_ISLNK(m)  (((m) & S_IFMT) == S_IFLNK)
# define FT_ISSOCK(m) (((m) & (unsigned int)S_IFMT) == S_IFSOCK)

#define FT_LS_____HL 0
#define FT_LS____UID 1
#define FT_LS___GUID 2
#define FT_LS_DRIVER 3
#define FT_LS___FILE 4
#define FT_LS___NAME 5
#define FT_LS_ARR_SZ 6

# define FT_LS_MAX_FILE 255

typedef struct s_ls
{
	int nb_elements;
	struct stat fs;
	DIR *dir;
	long options;
	int size_coll[FT_LS_ARR_SZ];
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
	char file[256];
	char link[256];
	int has_driver;
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
} t_f;

typedef struct s_file
{
	long sort_data;
	char name[FT_LS_MAX_FILE];
} t_file;


/*
**	classic option
** 	# define FT_LS_O_R	0001
**	# define FT_LS_O_l	0002
**	# define FT_LS_O_a	0004
**	# define FT_LS_O_r	0007
**	# define FT_LS_O_t	0010
**	# define FT_LS_O_n	0020
**	# define FT_LS_O_c	0040
**	# define FT_LS_O_S	0070
**	# define FT_LS_O_g	0100
*/


/*
**	option
*/
# define FT_LS_O_R    (1 << 0)
# define FT_LS_O_l    (1 << 1)
# define FT_LS_O_a    (1 << 2)
# define FT_LS_O_r    (1 << 3)
# define FT_LS_O_t    (1 << 4)
# define FT_LS_O_n    (1 << 5)
# define FT_LS_O_c    (1 << 6)
# define FT_LS_O_S    (1 << 7)
# define FT_LS_O_g    (1 << 8)
# define FT_LS_O_u    (1 << 9)
# define FT_LS_O_T    (1 << 10)

# define FT_LS_CUSTOM_SORT (FT_LS_O_t | FT_LS_O_c | FT_LS_O_S | FT_LS_O_u)

/*
**	functions
*/
char *get_time(long int *time, int mode, char *out);
int extract_lstat(struct stat *fs, t_f *f, t_ls *ls);
int ft_ls_sort(t_ls_2 *l);
int init_t_ls(char *path, t_ls *l);
int buffer_tab(t_ls *ls);
int is_directory(char *path);
int ft_ls_init(char *path, t_ls_2 *l);
void ft_ls_free(t_ls_2 *l);

/*
**	helpers
*/
int ft_api_lstat(t_ls_2 *l);
int ft_api_dir(t_ls_2 *l);
#endif
