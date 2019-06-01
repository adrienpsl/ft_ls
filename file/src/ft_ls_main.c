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

#include "ft_ls.h"

int ft_ls_option_parse(char *arg_str, t_ls *ls)
{
	return ft_io_catch_options(arg_str, "Rlart", &ls->options);
}

char *get_time(long int *time, int mode, char *out)
{
	if (mode)
		ft_mem_copy(out, ctime(time) + 4, 12);
	out[12] = 0;

	return (0);
}

static void norme_size_driver(t_file *f, t_ls *l)
{
	int size;

	size = l->size_coll[DRIVER_MAX_SIZE] ? l->size_coll[SIZE_SIZE] + 3
										 : l->size_coll[SIZE_SIZE];
	if (f->file_mode[0] == 'b' || f->file_mode[0] == 'c')
	{
		ft_sprintf(l->buff, "   %*d, ",
				   l->size_coll[DRIVER_MAX_SIZE],
				   f->driver[FT_LS_DRIVER_MAX]);
		ft_sprintf(l->buff, "%*d",
				   (l->size_coll[SIZE_SIZE]
					- (l->size_coll[DRIVER_MAX_SIZE] + 2)),
				   f->driver[FT_LS_DRIVER_MIN]);
	}
	else
		ft_sprintf(l->buff, "%*d", size, f->size);
}

int buffer_add_line(t_file *f, t_ls *l)
{
	char time[20];

	ft_mem_set(time, 0, 20);
	get_time(&f->mtime, 1, time);
	ft_sprintf(l->buff, "%s", f->file_mode);
	if (f->acl)
		ft_sprintf(l->buff, "+");
	else if (f->attr)
		ft_sprintf(l->buff, "@");
	else
		ft_sprintf(l->buff, " ");
	ft_sprintf(l->buff, " %*d", l->size_coll[HARD_LINK_SIZE], f->hard_link);
	ft_sprintf(l->buff, " %-*s", l->size_coll[UID_SIZE], f->uid);
	ft_sprintf(l->buff, "  %-*s", l->size_coll[GUID_SIZE], f->guid);
	norme_size_driver(f, l);
	ft_sprintf(l->buff, " %s", time);
	ft_sprintf(l->buff, " %s", f->name);
	if (f->file_mode[0] == 'l')
		ft_sprintf(l->buff, " -> %s", f->sym_real_file);
	ft_sprintf(l->buff, "\n");
	return (0);
}

int handle_lstast(char *path, t_file *f, t_ls *l)
{
	static struct stat fs;

	if (lstat(path, &fs))
		return (-1);
	if (FT_ISLNK(fs.st_mode))
		if (readlink(path, f->sym_real_file, FILE_NAME_MAX_SIZE) == -1)
			return (-1);
	ft_fill_line(&fs, f, l);
	return (0);
}

// je vais courir et ensuite je pourrai tester le print avec
// tout qui fait les meme valeurs ! et ca c'est super mon gars !
int get_acl_and_attr(char *path, t_file *f)
{
	acl_t acl;
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (acl > 0)
	{
		f->acl = 1;
		acl_free((void *) acl);
	}
	if (listxattr(path, NULL, 0, 0) > 0)
		f->attr = 1;
	return (0);
}

int loop_directory(DIR *dir, t_array *array, char *before_path, t_ls *ls)
{
	t_file *file;
	struct dirent *dp;
	char path[PATH_MAX + 1];
	size_t path_end;

	path_end = ft_str_len(before_path);
	ft_mem_set(&path, 0, PATH_MAX + 1);
	ft_mem_copy(path, before_path, path_end);
	path[path_end++] = '/';
	while ((dp = readdir(dir)) != NULL)
	{
		file = ft_array_next_el(array);
		file->name_size = ft_str_len(dp->d_name);
		ft_mem_copy(file->name, dp->d_name, file->name_size);
		ft_mem_copy(path + path_end, file->name, file->name_size);
		get_acl_and_attr(path, file);
		handle_lstast(path, file, ls);
		ft_mem_set(path + path_end, 0, file->name_size);
		if (ls->nb_elements == 12)
			(void) 1;
		ls->nb_elements++;
	}
	return (0);
}

// test path
// au tout debut, je cherche mon le directory de mon element demande
// et ensuite je

//int loop_dir(char *before_path)
//{
	// je regarde ce qu'est cet element
	// c'est un fichier > je print ses info

	// c'est un directory
	// je loop dessus et imprime son contenu

	// je le parcours et cherche des dossiers, si dossiers
	// je relance ma function avec le nouveau path.
	// je stock ce path dans un ls que je transmet. donc ca c'est en malloc
	// et c'est cool man !
//}



//int ft_read_directory(char *path, t_array *array_sort)
//{
//	t_ls ls;
//	DIR *dir;
////	t_array *array;
//
//
//	ft_mem_set(&ls, 0, sizeof(t_ls));
//	if (!(dir = opendir(path)))
//		return (-1);
////	loop_directory(dir, array_sort, path);
//
//
//	return (0);
//}