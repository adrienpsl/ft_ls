
// je veux le path absolu du file, ensuite
// je regarde si je print bien pour chaque 1 droit
// type
#include <errno.h>
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

void test_premission()
{
	// file
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

	// link
	if (utils_test_permission(FILE"linked", "lrwxr-xr-x"))
		ft_test_error("test_permission_8");

	// directory
	if (utils_test_permission(FILE"directory", "drwxr-xr-x"))
		ft_test_error("test_permission_9");

	// chr file
	if (utils_test_permission(FILE"lp0", "crw-r--r--"))
		ft_test_error("test_permission_10");

	//blk file
	if (utils_test_permission(FILE"MYFIFO", "brw-r--r--"))
		ft_test_error("test_permission_11");

	// fifo file
	if (utils_test_permission(FILE"a=rw", "prw-r--r--"))
		ft_test_error("test_permission_12");

}


void main_test()
{
	test_premission();

	t_ls_link link;
	t_ls ls;
	int ret;

	ret = ft_fill_link("aoueae", &link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_1");
//	perror("test");

	ret = ft_fill_link(FILE"/dir/toto", &link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_2");
//	perror("test");

	ret = ft_fill_link(NULL, &link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_3");
//	perror("test");



	// test opening right
	// file not existe
	// file name to big
	// no right file
	// no right path file

}
