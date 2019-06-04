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

// i need the s and the t at the end
void ft_ls_get_permission(const mode_t mode, char *file)
{
	static const char rights[] = "rwxrwxrwx";
	static int filters[7] = {S_IFBLK, S_IFCHR, S_IFIFO, S_IFDIR,
							 S_IFLNK, S_IFSOCK, S_IFREG};
	static char char_type[] = "bcpdls-";
	ssize_t i;

	i = -1;
	while (++i < 9)
	{
		file[i + 1] = (mode & (1 << (8 - i))) ? rights[i] : '-';
		if (i == 3 && (mode & S_ISUID))
			file[i] = file[i] == 'x' ? 's' : 'S';
		if (i == 6 && (mode & S_ISGID))
			file[i] = file[i] == 'x' ? 's' : 'S';
		if (i == 8 && (mode & S_ISVTX))
			file[i + 1] = file[i + 1] == 'x' ? 't' : 'T';
	}
	i = -1;
	while (++i < 7)
	{
		if ((S_IFMT & mode)  == filters[i])
		{
			file[0] = char_type[i];
			break;
		}
	}
}

//// TODO : add l'option -n
//// ici je vais print dans mon buffer, avec le sprintf
//int print_stats_element(t_ls_2 *l, t_file *file)
//{
//	// les droit et types du file
//	// les acl et @
//	// taille
//	// uid et guid //
//	// taille : si c'est le type drivers, ne pas tout print
//	// l'heure : gere si file too old ou too young + option T, je vais faire tt les test en T
//	// name file + if needed symlink
//}

// que print en foncion des options en long
int print_stats(t_ls_2 *l)
{
	t_file *file;
	size_t file_size;

	while ((file = (t_file *) ft_array_next_el(l->array)))
	{
		ft_str_len(&file_size, l->path);
		ft_mem_copy(l->path + l->end_path, file->name, file_size);
		if (ft_api_lstat(l))
			return (-1);
//		print_stats_element(l, file);
	}
	return (0);
}


// print en col

//