
// je veux le path absolu du file, ensuite
// je regarde si je print bien pour chaque 1 droit
// type
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/ttycom.h>
# include "ft_ls.h"


# define FILE "/Users/adpusel/code/42/ls/test/test_ls/"

// permission
int utils_test_permission(char *file, char *res)
{
	char buff[12];
	ft_mem_set(&buff, 0, 12);
	struct stat fileStat;

	lstat(file, &fileStat);

//	ft_get_permission(&fileStat.st_mode, buff);
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

/*// lstat
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

}*/

// test le buffer de l, je veux le fill avec mes datas :
//
int buffer_add_line(t_file *f, t_ls *l);

int init_lstat(t_file *f, t_ls *l);
int utils_fill_line(char *path, char *file_name, char *res)
{
	static int test_nb = 0;
	int ret = 0;
	size_t size;
	t_file *file;
	(void) res;


	// drwxr-xr-x          43 adpusel  staff      1376 Jun  2 14:29
	ft_str_len(&size, path);
	t_ls ls;
	init_t_ls("taat", &ls);
	ft_array_new(&ls.array, 12, sizeof(t_file));

	ft_mem_copy(ls.path, path, size);
	ls.path[size++] = '/';
	ft_mem_copy(ls.path + size, file_name, STRING_MODE);

	file = ft_array_next_el(ls.array);
	init_lstat(file, &ls);
	extract_lstat(&ls.fs, file, &ls);
	buffer_add_line(file, &ls);
	ft_buffer_clean(ls.buff);
//	init_t_ls(path, &ls);


	if (ret)
		ft_print_error("ft_fill_line ", test_nb);


	test_nb++;
	return ret;
}

void test_fill_line()
{
//	// directory d
	utils_fill_line("/dev/", ".",
					"drwxr-xr-x  2 root  staff  64 Jun  1 16:35 directory"
			//	"drwxr-xr-x  2 root  staff  64 Jun  1 16:35 directory"
	);
//
//	// file -
//	utils_fill_line("/Users/adpusel/code/42/ls/test/test_ls/", "42----rwxrwx",
//					"----rwxrwx  1 root  staff  0 Jun  1 16:35 42----rwxrwx");
//
//	// fifo -p
//	utils_fill_line("/Users/adpusel/code/42/ls/test/test_ls/", "fifofile",
//					"prw-r--r--  1 root  staff  0 Jun  1 16:35 fifofile");
//
//	// device : b
//	utils_fill_line("/dev/", "disk0",
//					"brw-r-----  1 root  operator   1, 0 May 28 07:12 disk0"
//	//				"brw-r-----  1 root  operator   1, 0 May 28 07:12 disk0"
//	);
//
// // device : c
//	utils_fill_line("/dev/", "xcpm",
//					"crw-rw----  1 root  _windowserver   19, 0 May 28 07:12 xcpm"
//	//				"crw-rw----  1 root  _windowserver   19, 0 May 28 07:12 xcpm"
//	);
//
// //  socket : c
//	utils_fill_line("/var/run/", "vpncontrol.sock",
//					"srw-------  1 root  daemon  0 May 28 07:12 vpncontrol.sock"
//	//				"srw-------  1 root  daemon  0 May 28 07:12 vpncontrol.sock "
//	);
//
//
// //  s link : l
//	utils_fill_line("/Users/adpusel/code/42/ls/test/test_ls/", "linked",
//					"lrwxr-xr-x  1 root  staff  12 Jun  1 16:35 linked -> 42----------"
//	//				"srw-------  1 root  daemon  0 May 28 07:12 vpncontrol.sock "
//	);

}

int build_files_array(t_ls *ls);
size_t length_itoa(int nb);
void set_max_length(int witch_size, int *size_array, int nb, char *str);

void test_loop_directory()
{

//	t_file *file;

	t_ls ls;

	ft_mem_set(&ls, 0, sizeof(ls));
	ft_buffer_new(&ls.buff, 2000, 1);


	init_t_ls("/Users/adpusel/Documents", &ls);

	build_files_array(&ls);
//	ls.size_coll[SIZE_SIZE] += (2 + ls.size_coll[DRIVER_MAX_SIZE]);
//	ft_ls_sort(&ls, array, ls.nb_elements);
//	array->i = 0;
//	int i = 0;
//	while (i < ls.nb_elements)
//	{
//		file = ft_array_el(array, i);
//		buffer_add_line(file, &ls);
//		ft_buffer_clean(ls.buff);
//		i++;
//	}
//	printf("%d \n", strcmp(tt, ls.buff->data));
//	ft_buffer_clean(ls.buff);

}


void test_init_t_ls()
{
	t_ls ls;

	init_t_ls("/Users/adpusel", &ls);
	if (strcmp(ls.path, "/Users/adpusel") || ls.nb_elements != 43)
		ft_test_error("init ls 1");
}

// display with column


void main_test()
{

//	utils_fill_line("/Users/adpusel", ".", "tat");
//
//	t_ls ls;
//	init_t_ls("/Users/adpusel", &ls);
//	memset(&ls, 0, sizeof(t_ls));
//	init_t_ls("/Users/adpusel", &ls);
//	build_files_array(&ls);
//	ft_ls_sort(&ls);
//	buffer_tab(&ls);
//	ft_buffer_clean(ls.buff);


	//	test_premission();
//	test_lstat();
//	test_fill_line();
//	test_loop_directory();
//	test_init_t_ls();

//	printf("%d \n", ft_read_directory("./aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe/aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe/aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe/aeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoeuaeouaoeuaoeuaoe", NULL));
//	perror("tat");


}
