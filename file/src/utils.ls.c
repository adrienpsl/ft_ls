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


int ft_ls_sort_func(void *p_l1, void *p_l2, void *p_param)
{
	t_ls_link *l1;
	t_ls_link *l2;
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
	// si pas t retur with name
}