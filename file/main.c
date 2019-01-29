#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include "all_includes.h"

#define NOT_FOUND 2
#define ERROR 3
#define FOUND 1

#define	FT_ISBLK(m)	 (((m) & (unsigned int)S_IFMT) == S_IFBLK)
#define	FT_ISCHR(m)	 (((m) & (unsigned int)S_IFMT) == S_IFCHR)
#define	FT_ISDIR(m)	 (((m) & (unsigned int)S_IFMT) == S_IFDIR)
#define	FT_ISFIFO(m) (((m) & (unsigned int)S_IFMT) == S_IFIFO)
#define	FT_ISLNK(m)  (((m) & (unsigned int)S_IFMT) == S_IFLNK)
#define	FT_ISSOCK(m) (((m) & (unsigned int)S_IFMT) == S_IFSOCK)


char getType(const mode_t *st_mode_ptr)
{
	const mode_t st_mode = *st_mode_ptr;

	if (FT_ISBLK(st_mode))
		return 'b';
	if (FT_ISCHR(st_mode))
		return 'c';
	if (FT_ISDIR(st_mode))
		return 'd';
	if (FT_ISFIFO(st_mode))
		return 'p';
	if (FT_ISLNK(st_mode))
		return 's';
	if (FT_ISSOCK(st_mode))
		return 's';
	else
		return '-';
}

void getPermission(const mode_t *st_mode_ptr, char *fileMode)
{
	// cette belle petite fonction me print les droits
	const mode_t st_mode = *st_mode_ptr;

	printf("File Permissions: \t");

	// une fonction pour le type du fichier
	fileMode[0] = getType(st_mode_ptr);

	// ce que je dois tester pour les droits
	fileMode[1] = st_mode & (unsigned int)S_IRUSR ? 'r' : '-';
	fileMode[2] = st_mode & (unsigned int)S_IWUSR ? 'w' : '-';
	fileMode[3] = st_mode & (unsigned int)S_IXUSR ? 'x' : '-';
	fileMode[4] = st_mode & (unsigned int)S_IRGRP ? 'r' : '-';
	fileMode[5] = st_mode & (unsigned int)S_IWGRP ? 'w' : '-';
	fileMode[6] = st_mode & (unsigned int)S_IXGRP ? 'x' : '-';
	fileMode[7] = st_mode & (unsigned int)S_IROTH ? 'r' : '-';
	fileMode[8] = st_mode & (unsigned int)S_IWOTH ? 'w' : '-';
	fileMode[9] = st_mode & (unsigned int)S_IXOTH ? 'x' : '-';
	printf("\n");
	// je print le resultat de tout ca ! :)
}

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

int main()
{
	DIR *currentDir;
	struct dirent *dp;
	struct stat fileStat; // donner a stats
	int ret;
	static char fileMode[10] = { 0 };

	// j'ouvre le dir current, pour commencer le chemin
	currentDir = opendir(".");

	// je verifie que tout se passe bien
	if (currentDir == NULL)
		return (ERROR);

	// a chaque iteration j'ouvre le file
	dp = readdir(currentDir);
	printf("%s \n", dp->d_name);
	dp = readdir(currentDir);
	printf("%s \n", dp->d_name);


	// file 1 =======================================

	// j'open ce ptr pour interagir avec son contenu
	dp = readdir(currentDir);

	// je print sont nom
	printf("%s \n", dp->d_name); // c'est sont nom, je ne sais pas si je peux le

	// je verifie sont retour
	ret = stat(dp->d_name, &fileStat);

	// je print ses permissions
	ft_printf(" \n");
	getPermission(&fileStat.st_mode, fileMode);
	ft_printf("%s \n", fileMode);





	// file 2 ======================================
	dp = readdir(currentDir);
	printf("%s \n", dp->d_name);
	// retourn les deux premier shit de tout dossier


	return 0;
}
