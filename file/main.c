
#include <ft_libft_struct.h>
#include "ft_ls.h"


#define NOT_FOUND 2
#define ERROR 3
#define FOUND 1
void main_test();

int findDir(char *name)
{
	DIR *dirp;
	size_t len;
	struct dirent *dp;

	dirp = opendir(".");
	if (dirp == NULL)
		return (ERROR);
	len = strlen(name);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0)
		{
			(void) closedir(dirp);
			return (FOUND);
		}
	}
	(void) closedir(dirp);
	return (NOT_FOUND);
}

// je vais prendre une taille de 300 fichier

void printAllName(DIR *head_list)
{
	struct dirent *dp;

	dp = readdir(head_list);
	while (dp)
	{
		printf("%s \n", dp->d_name);
		dp = readdir(head_list);
	}
}


void test(struct stat sb)
{

	printf("Type de fichier :                ");

	switch (sb.st_mode & S_IFMT)
	{
		case S_IFBLK:
			printf("périphérique de bloc\n");
			break;
		case S_IFCHR:
			printf("périphérique de caractère\n");
			break;
		case S_IFDIR:
			printf("répertoire\n");
			break;
		case S_IFIFO:
			printf("FIFO/tube\n");
			break;
		case S_IFLNK:
			printf("lien symbolique\n");
			break;
		case S_IFREG:
			printf("fichier ordinaire\n");
			break;
		case S_IFSOCK:
			printf("socket\n");
			break;
		default:
			printf("inconnu ?\n");
			break;
	}

	printf("Numéro d'inœud :                   %ld\n", (long) sb.st_ino);

	printf("Mode :                             %lo (octal)\n",
		   (unsigned long) sb.st_mode);

	printf("Nombre de liens :                  %ld\n", (long) sb.st_nlink);
	printf("Propriétaires :                    UID=%ld   GID=%ld\n",
		   (long) sb.st_uid, (long) sb.st_gid);

	printf("Taille de bloc d’E/S :             %ld octets\n",
		   (long) sb.st_blksize);
	printf("Taille du fichier :                %lld octets\n",
		   (long long) sb.st_size);
	printf("Blocs alloués :                    %lld\n",
		   (long long) sb.st_blocks);

	printf("Dernier changement d’état :        %s", ctime(&sb.st_ctime));
	printf("Dernier accès au fichier :         %s", ctime(&sb.st_atime));
	printf("Dernière modification du fichier:  %s", ctime(&sb.st_mtime));

	exit(EXIT_SUCCESS);
}


DIR *_open_dir(const char *filename);


char *get_time(long int *time, int mode, char *out)
{
	if (mode)
		ft_mem_copy(out, ctime(time) + 4, 12);
	out[12] = 0;

	return (0);
}



int ft_ls_sort_func(void *p_l1, void *p_l2, void *p_param);

void print_list(int nb_elements, t_array *array, t_ls *ls)
{

	t_ls_link *link1;
	char date[13];


	while (nb_elements--)
	{
		link1 = ft_array_next_el(array);

		get_time(&link1->mtime, 1, date);
//		printf("%s %d %s %s %lld, %s, %s\n",
//			   link1->file_mode,
//			   link1->hard_link,
//			   getpwuid(link1->uid)->pw_name,
//			   getgrgid(link1->guid)->gr_name,
//			   link1->size,
//			   date,
//			   link1->name
//		);
		ft_printf("%s %*d %*s %*s %*lld %s ",
				  link1->file_mode,
				  ls->size_coll[HARD_LINK_SIZE],
				  link1->hard_link,
				  ls->size_coll[UID_SIZE],
				  link1->uid,
				  ls->size_coll[GUID_SIZE],
				  link1->guid,
				  ls->size_coll[SIZE_SIZE],
				  link1->size,
				  date);
		write(1, link1->name, link1->name_size);
		if (*link1->sym_real)
			ft_printf(" -> %s", link1->sym_real);
		putchar('\n');
	}
}

int main()
{
	main_test();


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


