#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "all_includes.h"


#define NOT_FOUND 2
#define ERROR 3
#define FOUND 1

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


#define    FT_ISBLK(m)     (((m) & (unsigned int)S_IFMT) == S_IFBLK)
#define    FT_ISCHR(m)     (((m) & (unsigned int)S_IFMT) == S_IFCHR)
#define    FT_ISDIR(m)     (((m) & (unsigned int)S_IFMT) == S_IFDIR)
#define    FT_ISFIFO(m) (((m) & (unsigned int)S_IFMT) == S_IFIFO)
#define    FT_ISLNK(m)  (((m) & (unsigned int)S_IFMT) == S_IFLNK)
#define    FT_ISSOCK(m) (((m) & (unsigned int)S_IFMT) == S_IFSOCK)

char ft_get_type(const mode_t *st_mode_ptr)
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

void ft_get_permission(const mode_t *st_mode, char *fileMode)
{
	fileMode[0] = ft_get_type(st_mode);
	fileMode[1] = *st_mode & (unsigned int) S_IRUSR ? 'r' : '-';
	fileMode[2] = *st_mode & (unsigned int) S_IWUSR ? 'w' : '-';
	fileMode[3] = *st_mode & (unsigned int) S_IXUSR ? 'x' : '-';
	fileMode[4] = *st_mode & (unsigned int) S_IRGRP ? 'r' : '-';
	fileMode[5] = *st_mode & (unsigned int) S_IWGRP ? 'w' : '-';
	fileMode[6] = *st_mode & (unsigned int) S_IXGRP ? 'x' : '-';
	fileMode[7] = *st_mode & (unsigned int) S_IROTH ? 'r' : '-';
	fileMode[8] = *st_mode & (unsigned int) S_IWOTH ? 'w' : '-';
	fileMode[9] = *st_mode & (unsigned int) S_IXOTH ? 'x' : '-';
}


int read_link(int argc, char *argv[])
{
	struct stat sb;
	char *buf;
	ssize_t nbytes, bufsiz;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (lstat(argv[1], &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	/* Add one to the link size, so that we can determine whether
	   the buffer returned by readlink() was truncated. */

	bufsiz = sb.st_size + 1;

	/* Some magic symlinks under (for example) /proc and /sys
	   report 'st_size' as zero. In that case, take PATH_MAX as
	   a "good enough" estimate. */

	if (sb.st_size == 0)
		bufsiz = PATH_MAX;

	buf = malloc(bufsiz);
	if (buf == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	nbytes = readlink(argv[1], buf, bufsiz);
	if (nbytes == -1)
	{
		perror("readlink");
		exit(EXIT_FAILURE);
	}

	printf("'%s' points to '%.*s'\n", argv[1], (int) nbytes, buf);

	/* If the return value was equal to the buffer size, then the
	   the link target was larger than expected (perhaps because the
	   target was changed between the call to lstat() and the call to
	   readlink()). Warn the user that the returned target may have
	   been truncated. */

	if (nbytes == bufsiz)
		printf("(Returned buffer may have been truncated)\n");

	free(buf);
	exit(EXIT_SUCCESS);
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

// open, read, class les elements du path donne
// test :

//int

// function qui me return le tab

// fuction to check the tim
char *get_time(long int *time, int mode, char *out)
{
	char *ret;
	if (mode)
	{
		ret = ctime(time);
		ft_mem_copy(out, ctime(time) + 4, 12);
	}
	out[12] = 0;

	return (0);
}


int main()
{
	DIR *currentDir;
	struct dirent *dp;
	int ret;
	char date[13];
//  je met tout ca dans un tab que je trie en fonction de la method de trie,
//  je vais peux etre avoir plusieur trie possible !


// je loup la dessus pour avoir le nom de tous les file inside this dir
//	printAllName(currentDir);


	int nbBlock = 0;
	struct stat fileStat;
	ts_ls_link lk;
	ft_mem_set(&lk, 0, sizeof(ts_ls_link));

	char *path_name = "test";
	currentDir = opendir(path_name);

	// check le retour de read dir, et les err qu'il retourn
	dp = readdir(currentDir);
	lk.name_size = ft_str_len(dp->d_name);
	ft_mem_copy(lk.name, dp->d_name, lk.name_size);

	// check le ret
	ret = stat(dp->d_name, &fileStat);
	nbBlock += fileStat.st_blocks;

	ft_get_permission(&fileStat.st_mode, lk.file_mode);

	lk.hard_link = fileStat.st_nlink;
	lk.uid = fileStat.st_uid;
	lk.guid = fileStat.st_gid;
	lk.size = fileStat.st_size;
	lk.mtime = fileStat.st_mtime;

	get_time(&lk.mtime, 1, date);
	printf("%s %d %s %s %lld, %s",
		   lk.file_mode,
		   lk.hard_link,
		   getpwuid(lk.uid)->pw_name,
		   getgrgid(lk.guid)->gr_name,
		   lk.size,
		   date
	);




//	ret = stat("/Users/adpusel/Downloads/papier-20190528T062221Z-001.zip", &fileStat);
//	test(fileStat);
//	printf("%d \n", ret);
//	ft_get_permission(&fileStat.st_mode, fileMode);

	// I got fileStat struct, i want get the group of the user


	// je print ses permissions
	printf(" \n");

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


