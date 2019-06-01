
// je veux le path absolu du file, ensuite
// je regarde si je print bien pour chaque 1 droit
// type
#include <errno.h>
# include "ft_ls.h"

void ft_get_permission(const mode_t *st_mode, char *fileMode);

# define FILE "/Users/adpusel/code/42/ls/test/test_ls/"

// permission
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

// lstat
int handle_lstast(char *path, t_file *f, t_ls *l);
void test_lstat()
{
	t_file link;
	t_ls ls;
	int ret;

	ret = handle_lstast("aoueae", &link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_1");
//	perror("test");

	ret = handle_lstast(FILE"/dir/toto", &link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_2");
//	perror("test");

	ret = handle_lstast(NULL, &link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_3");
//	perror("test");

	ret = handle_lstast((char *) 1223, &link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_3");
//		perror("test");


	ret = handle_lstast(
			"oeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehuoeuhaoseuhaoeuhaoeuhosanuhaoeuhaonehu",
			&link, &ls);
	if (ret != -1)
		ft_test_error("fill_link_3");
//			perror("test");

//	ret = ft_fill_link("/dev/disk1s2", &link, &ls);
	ret = handle_lstast("/Users/adpusel/code/42/ls/test/test_ls/saluet", &link, &ls);

}

// test le buffer de l, je veux le fill avec mes datas :
//
int buffer_add_line(t_file *f, t_ls *l);

int utils_fill_line(char *path, char *file_name, char *res)
{
	t_file file;
	t_ls ls;
	size_t size;
	int ret;
	char full_path[PATH_MAX];
	static int test_nb = 0;

	size = strlen(path);
	ft_mem_copy(full_path, path, size);
	ft_mem_copy(full_path + size, file_name, strlen(file_name));

	size = ft_str_len(file_name);
	ft_mem_copy(file.name, file_name, size);
	file.name_size = size;

	ft_buffer_new(&ls.buff, 100, 1);

	handle_lstast(full_path, &file, &ls) || buffer_add_line(&file, &ls);
	ret = strcmp(res, ls.buff->data);


	ft_buffer_free(&ls.buff);
	if (ret)
		ft_print_error("ft_fill_line ", test_nb);

	test_nb++;
	return ret;
}

void test_fill_line()
{
	// directory d
	utils_fill_line("/Users/adpusel/code/42/ls/test/test_ls/", "directory",
					"drwxr-xr-x  2 root  staff  64 Jun  1 16:35 directory"
				//	"drwxr-xr-x  2 root  staff  64 Jun  1 16:35 directory"
	);

	// file -
	utils_fill_line("/Users/adpusel/code/42/ls/test/test_ls/", "42----rwxrwx",
					"----rwxrwx  1 root  staff  0 Jun  1 16:35 42----rwxrwx");

	// fifo -p
	utils_fill_line("/Users/adpusel/code/42/ls/test/test_ls/", "fifofile",
					"prw-r--r--  1 root  staff  0 Jun  1 16:35 fifofile");

	// device : b
	utils_fill_line("/dev/", "disk0",
					"brw-r-----  1 root  operator   1, 0 May 28 07:12 disk0"
	//				"brw-r-----  1 root  operator   1, 0 May 28 07:12 disk0"
	);

 // device : c
	utils_fill_line("/dev/", "xcpm",
					"crw-rw----  1 root  _windowserver   19, 0 May 28 07:12 xcpm"
	//				"crw-rw----  1 root  _windowserver   19, 0 May 28 07:12 xcpm"
	);

 //  socket : c
	utils_fill_line("/var/run/", "vpncontrol.sock",
					"srw-------  1 root  daemon  0 May 28 07:12 vpncontrol.sock"
	//				"srw-------  1 root  daemon  0 May 28 07:12 vpncontrol.sock "
	);


 //  s link : l
	utils_fill_line("/Users/adpusel/code/42/ls/test/test_ls/", "linked",
					"lrwxr-xr-x  1 root  staff  12 Jun  1 16:35 linked -> 42----------"
	//				"srw-------  1 root  daemon  0 May 28 07:12 vpncontrol.sock "
	);

}

void main_test()
{
//	test_premission();
//	test_lstat();
//	test_fill_line();


//	printf("%d \n", ft_read_directory("./aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe/aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe/aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe/aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe", NULL));
//	perror("tat");


}
