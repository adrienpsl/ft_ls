# include <ft_ls.h>
# include "../file/src/src_2/ft_ls_handle_stat.c"
# include "../file/src/src_2/ft_ls_print_2.c"

/* test main ------------------------------------------------------------ */

void helper_test()
{
	t_ls_2 ls2;
	t_ls_2 *l;
	l = &ls2;
	ft_mem_set(&ls2, 0, sizeof(ls2));

	ft_mem_copy(ls2.path, "/dev", 4);
	if (ft_api_lstat(l) || ft_api_dir(l))
		ft_test_error("ft_api_lstat");

	ft_mem_copy(ls2.path, "/devl", 5);
	if (!ft_api_lstat(l) || !ft_api_dir(l))
		ft_test_error("ft_api_lstat");

}

void test_init_ls_2()
{
	t_ls_2 ls2;
	t_ls_2 *l;
	l = &ls2;
	int ret;

	// test with good argv
	ret = ft_ls_init("/Users/adpusel", l);
	if (ret
		|| l->array->length != 44
		|| strcmp("/Users/adpusel", l->path))
		ft_test_error("test_init_ls 1");
	ft_ls_free(l);

	// test with good arg
	ret = ft_ls_init("/Users/adpuselaoeu", l);
	if (!ret || l->array || strcmp("/Users/adpuselaoeu", l->path))
		ft_test_error("test_init_ls 2");
}

/* test stat ------------------------------------------------------------ */
void test_ft_ls_max()
{
	int arr[FT_LS_ARR_SZ] = {0};

	// test with null
	ft_ls_max(&arr[2], 10, NULL);
	if (arr[2] != 2)
		ft_test_error("test_ft_ls_max 1");

	// test with str
	ft_ls_max(&arr[4], 10, "1122");
	if (arr[4] != 4)
		ft_test_error("test_ft_ls_max 2");
}

void test_ft_set_max()
{
	t_ls_2 l;

	printf("%lu-- \n", sizeof(long));
	// regular file
	int download_file[6] = {2, 7, 5, 0, 4, 9};
	ft_mem_set(&l, 0, sizeof(t_ls_2));
	lstat("/Users/adpusel/Downloads", &l.fs);
	ft_set_max(&l, "Downloads");
	if (test_cmp_int_array(download_file, l.size, 6))
		ft_test_error("test_ft_set_max 1");


	// driver
	int driver[6] = {1, 7, 3, 2, 1, 7};
	ft_mem_set(&l, 0, sizeof(t_ls_2));
	lstat("/dev/ttys000", &l.fs);
	ft_set_max(&l, "ttys000");
	if (test_cmp_int_array(driver, l.size, 6))
		ft_test_error("test_ft_set_max 2");


	// FT_LS_O_n trigger
	int option[6] = {2, 3, 2, 0, 4, 9};
	ft_mem_set(&l, 0, sizeof(t_ls_2));
	lstat("/Users/adpusel/Downloads", &l.fs);
	l.options |= FT_LS_O_n;
	ft_set_max(&l, "Downloads");
	if (test_cmp_int_array(option, l.size, 6))
		ft_test_error("test_ft_set_max 3");

	// FT_LS_O_n trigger
	ft_mem_set(&l, 0, sizeof(t_ls_2));
	lstat("/Users/adpusel/Downloads", &l.fs);

}

void test_fill_file()
{
	t_ls_2 ls;
	t_ls_2 *l = &ls;
	t_file f;

	ft_mem((void **) &f, 1000);
	char date[200] = {0};

	// test t option
	ft_mem_set(date, 0, 200);
	ft_mem_copy(ls.path, "/tmp/toto/change", STRING_MODE);
	l->options |= FT_LS_O_t;
	ft_api_lstat(l);
	ft_get_sort_data(l, &f);
	ft_mem_copy(date, ctime(&f.sort_data) + 4, STRING_MODE);
	if (strcmp("Jun  3 13:27:24 2019\n", date))
		ft_test_error("ft_get_sort_data 1");

	// test avec u
	l->options = 0;
	ft_mem_copy(ls.path, "/tmp/toto/change", STRING_MODE);
	l->options |= FT_LS_O_u;
	ft_api_lstat(l);
	ft_get_sort_data(l, &f);
	ft_mem_copy(date, ctime(&f.sort_data) + 4, STRING_MODE);
	if (strcmp("Jun  3 13:27:24 2019\n", date))
		ft_test_error("ft_get_sort_data 2");

	// test avec c
	l->options = 0;
	ft_mem_copy(ls.path, "/tmp/toto/change", STRING_MODE);
	l->options |= FT_LS_O_c;
	ft_api_lstat(l);
	ft_get_sort_data(l, &f);
	ft_mem_copy(date, ctime(&f.sort_data) + 4, STRING_MODE);
	if (strcmp("Jun  3 13:27:28 2019\n", date))
		ft_test_error("ft_get_sort_data 3");

}

void test_array_file_name()
{
	t_ls_2 ls;
	t_ls_2 *l = &ls;
	int ret;

	ft_ls_init("/Users/adpusel", l);
	ret = array_file_name(l);
	int max_size[6] = {4, 7, 5, 0, 5, 38};
	if (ret
		|| strcmp(l->path, "/Users/adpusel/")
		|| l->end_path != 15
		|| test_cmp_int_array(max_size, l->size, 6)
		|| l->total != 408)
	{
		ft_test_error("test array_file_name 1");
		test_print_int_array(l->size, 6);
	}
	ft_ls_free(l);

	ft_ls_init("/dev", l);
	l->options |= FT_LS_O_a;
	ret = array_file_name(l);
	int driver_size[6] = {1, 7, 13, 2, 5, 29};
	if (ret
		|| strcmp(l->path, "/dev/")
		|| l->end_path != 5
		|| test_cmp_int_array(driver_size, l->size, 6)
		|| l->total != 0)
	{
		ft_test_error("test array_file_name 2");
		test_print_int_array(l->size, 6);
	}

}


/* test print --------------------------------------------------------------- */
void utils_print_permission(char *path, char *res)
{
	struct stat fs;
	char buff[300];
	static int nb;
	(void) res;

	ft_mem_set(buff, 0, 300);
	lstat(path, &fs);
	ft_ls_get_permission(fs.st_mode, buff);
	if (strcmp(res, buff))
	{
		ft_print_error("print_permission ", nb);
		printf("ls   : %s \n", res);
		printf("buff : %s \n", buff);
	}
	nb++;
}
void test_print_permission()
{
	// block special
	utils_print_permission("/dev/disk0", "brw-r-----");
	utils_print_permission("/Users/adpusel/.zshrc", "-rw-r--r--");
	utils_print_permission("/Users/adpusel/Applications", "drwx------");
	utils_print_permission("/dev/stderr", "lr-xr-xr-x");
	utils_print_permission("/dev/ttyv0", "crw-rw-rw-");
	utils_print_permission("/tmp/toto/fifo", "prw-r--r--");
	utils_print_permission("/var/run/pppconfd", "srwxrwxrwx");

	// uid
	utils_print_permission("/tmp/toto/uid-guid/uids_big", "-rwSr--r--");
	utils_print_permission("/tmp/toto/uid-guid/uids_little", "-rws------");

	// guid
	utils_print_permission("/tmp/toto/uid-guid/gids_big", "-rwx--Srwx");
	utils_print_permission("/tmp/toto/uid-guid/gids_little", "-rwxrws---");

	// t
	utils_print_permission("/tmp/toto/uid-guid/sticky_big", "-rw-r--r-T");
	utils_print_permission("/tmp/toto/uid-guid/sticky_little", "-rwx---rwt");
}

void test_get_acl_extended()
{
	char buff[2] = {0};

	ft_get_acl_extended("/Users/adpusel/.", buff);
	if (strcmp("+", buff))
		ft_test_error("get_acl_extended");

	ft_get_acl_extended("/Users/adpusel/Applications/.", buff);
	if (strcmp("@", buff))
		ft_test_error("get_acl_extended");

	ft_get_acl_extended("/Users/adpusel/code/.", buff);
	if (strcmp(" ", buff))
		ft_test_error("get_acl_extended");

	printf("%s \n", buff);
}

void util_print_time(char *path, char *res, long option)
{
	char buff[100] = {0};
	struct stat stat;
	static int nb = 0;

	lstat(path, &stat);
	print_time(stat.st_mtimespec.tv_sec, buff, option);
	if (strcmp(res, buff))
	{
		ft_print_error("print time", nb);
		printf("%s- \n", buff);
		printf("%s- \n", res);
	}
	nb++;
}

void test_print_time()
{
	// past and next file
	util_print_time("/tmp/toto/future", "Mar  2  2030", 0);
	util_print_time("/tmp/toto/past", "Sep  2  1990", 0);
	util_print_time("/tmp/toto/future", "Mar  2 03:03:00 2030", FT_LS_O_T);

	// classic file
	util_print_time("/tmp/toto/modify", "Jun  3 13:27", 0);
	util_print_time("/tmp/toto/modify", "Jun  3 13:27:26 2019", FT_LS_O_T);



	// test with goo date

	// test with option T

	// test with date too old

	// test with date too big

//	"Sat Mar  2 03:03:00 2030\n"


}


void test_print_long()
{
	// test nop diver


}

/* test sort ---------------------------------------------------------------- */



void main_test_2()
{
	helper_test();
	test_init_ls_2();
	test_ft_ls_max();
	test_ft_set_max();
//	test_array_file_name();
//	test_fill_file();
//	test_print_permission();
//	test_get_acl_extended();
	test_print_time();
}
