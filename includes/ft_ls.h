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

typedef struct s_file
{
	char dir;
	long sort_data;
	char name[1065];
} t_file;

typedef struct s_ls
{
	int elements;
	long options;
	size_t end_path;
	size_t size[6];
	long total;
	char path[PATH_MAX + 1];
	struct stat fs;
	DIR *dir;
	t_buffer *buff;
	t_array *array;
	char link_ptr[PATH_MAX + 1];
	int has_driver;
	t_file *f;
	int i;
	int y;
	size_t s;
	int is_path;
	int ret;
	int option_catched;
	int multiple_file;

} t_ls;


# define FT_LS_MODE_DIR 0
# define FT_LS_MODE_FILE 1

typedef struct s_ft_ls
{
	char **av;
	int ac;
	long options;
	int mode;
	int has_path;
	int i;
	t_buffer *buff;
	t_ls ls;
	t_file file;
	t_array *argv;
	t_sort sort;
} t_ft_ls;


# define FT_LS_DRIVER_MIN 0
# define FT_LS_DRIVER_MAX 1

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
# define FT_LS_O_1    (1 << 11)
/*
**	is use to set when ls has more that one argv
*/
# define FT_LS_O_M    (1 << 12)


# define FT_LS_CUSTOM_SORT (FT_LS_O_t | FT_LS_O_c | FT_LS_O_S | FT_LS_O_u)

/*
**	sorting function
*/
void ft_swap_file(void *a, void *b);
int ft_cmp_file(void *p_l1, void *p_l2, void *p_param);
void ft_swap_char(void *a, void *b);
int ft_cmp_char(void *a, void *b, void *p_param);

/*
**	functions
*/
char *get_time(long int *time, int mode, char *out);
int ft_ls_sort(t_ls *l);
int is_directory(char *path);
int ft_ls_init(char *path, t_ls *l, t_buffer *buff, long options);
void ft_ls_free(t_ls *l);

int get_lstat_and_filename(t_ls *l);
int ft_handle_dir(char *path, int options, t_buffer *buff, char *dir_name);

/*
**	print function
*/
int print_stats(t_ls *l);
void ft_ls_get_permission(const mode_t mode, char *file);
int ft_get_acl_extended(char *path, char *buff);
int print_time(long int time_nb, char *out, long option);
int print_all_col(t_ls *l);
int print_all(t_ls *l);
void print_err(char *dir_name);

/*
**	helpers
*/
int ft_api_lstat(t_ls *l);
int ft_api_dir(t_ls *l);
#endif
