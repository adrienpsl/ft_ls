#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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
