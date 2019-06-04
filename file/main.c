
#include <ft_libft_struct.h>
#include "ft_ls.h"
void main_test_2();

int main()
{
	main_test_2();


//	DIR *current_dir;
//
//	current_dir = opendir("test");
//	t_array *array;
//	struct dirent *dp;
//	t_ls_link *link1;
//	int nb_elements = 0;
//	char *path;
//	t_ls ls;
//	ft_mem_set(&ls, 0, sizeof(ls));
//
//	ft_array_new(&array, 200, sizeof(t_ls_link));
//
//	printf("%d \n", PATH_MAX);


//	struct stat fileStat;

//	lstat("test/toto", &fileStat);
//	test(fileStat);

//
//	while ((dp = readdir(current_dir)) > 0)
//	{
//		link1 = ft_array_next_el(array);
//		// je set le nom de mon file avant
//		link1->name_size = ft_str_len(dp->d_name);
//		ft_mem_copy(link1->name, dp->d_name, link1->name_size);
//
//		ft_str_join(&path, "test/", link1->name);
//
//		ft_fill_link(path, link1, &ls);
//		nb_elements++;
//	}
//
//	array->i = 0;
//
//
//
//	print_list(nb_elements, array, &ls);
//	array->i = 0;
//	print_list(nb_elements, array, &ls);
//
//	//	int nbBlock = 0;




	// check le retour de read dir, et les err qu'il retourn







//	ret = stat("/Users/adpusel/Downloads/papier-20190528T062221Z-001.zip", &fileStat);
//	test(fileStat);
//	printf("%d \n", ret);
//	ft_get_permission(&fileStat.st_mode, fileMode);

	// I got fileStat struct, i want get the group of the user


	// je print ses permissions

//	printf("%s \n", fileMode);
//	printf("----%d  --- %d\n", MAXPATHLEN, sizeof(t_ls) * 200); // 240000 // 200 kio
//
//
//
//
//
//	// file 2 ======================================
//	dp = readdir(currentDir);
//	printf("%s \n", dp->d_name);
	// retourn les deux premier shit de tout dossier


	return 0;
}


