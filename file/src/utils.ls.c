#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ft_ls.h>

void exit_and_display_error(int ret_function)
{
	if (ret_function)
	{
		perror("exit: ");
		exit(EXIT_FAILURE);
	}
}

DIR *_open_dir(const char *filename)
{
	DIR *ret;

	ret = opendir(filename);
	if (ret == NULL)
		perror("le fichier a ouvrir n'existe pas");
	return (ret);
}

void swap_func(void *a, void *b)
{
	t_file tmp;
	ft_mem_copy(&tmp, a, sizeof(t_file));
	ft_mem_copy(a, b, sizeof(t_file));
	ft_mem_copy(b, &tmp, sizeof(t_file));
}

int sort_func(void *p_l1, void *p_l2, void *p_param)
{
	t_file *l1;
	t_file *l2;
	long param;
	int ret;

	param = *(long *) p_param;
	l1 = p_l1;
	l2 = p_l2;

	// si t return by t
//	if (param & FT_LS_TIME)
//		return 1;
//	else
		ret =  ft_mem_cmp(l1->name, l2->name, FILE_NAME_MAX_SIZE) >= 0 ? 0 : 1;

	return  param & FT_LS_REVERSE ? !ret : ret;
}

void ft_ls_sort(t_ls *ls, t_array *array, int nb_elements)
{
	t_quick quick;

	quick.swap_func = swap_func;
	quick.array = array;
	quick.param = &ls->options;
	quick.cmp_func = sort_func;
	ft_quick_sort(&quick, 0, nb_elements - 1);
}