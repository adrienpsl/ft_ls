
// je veux le path absolu du file, ensuite
// je regarde si je print bien pour chaque 1 droit
// type
# include "ft_ls.h"

void ft_get_permission(const mode_t *st_mode, char *fileMode);

# define FILE "/Users/adpusel/code/42/ls/test/test_ls/"

int utils_test_permission(char *file, char *res)
{
	char buff[12];
	ft_mem_set(&buff, 0, 12);
	struct stat fileStat;

	lstat(file, &fileStat);

	ft_get_permission(&fileStat.st_mode, buff);
	return strcmp(res, buff);
}


void main_test()
{
	// test permission file
	if (utils_test_permission(FILE"42-rwxrwxrwx", "-rwxrwxrwx"))
		ft_test_error("test_permission_1");
	if (utils_test_permission(FILE"42----------", "----------"))
		ft_test_error("test_permission_2");
	if (utils_test_permission(FILE"42------x--x", "------x--x"))
		ft_test_error("test_permission_3");
	if (utils_test_permission(FILE"42----rwxrwx", "----rwxrwx"))
		ft_test_error("test_permission_4");
	if (utils_test_permission(FILE"42-r-xr-xr-x", "-r-xr-xr-x"))
		ft_test_error("test_permission_5");
	if (utils_test_permission(FILE"42-rwxrwxrwx", "-rwxrwxrwx"))
		ft_test_error("test_permission_6");
	if (utils_test_permission(FILE"42-w--w--w--", "--w--w--w-"))
		ft_test_error("test_permission_7");

}
