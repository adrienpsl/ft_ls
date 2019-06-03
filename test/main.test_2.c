# include <ft_ls.h>
# include "../file/src/src_2/ft_ls_main_2.c"

int init_ls_2(char *path, t_ls_2 *l);
void ls_free(t_ls_2 *l);
int ft_set_max(t_ls_2 *l, char *file_name);
int array_file_name(t_ls_2 *l);

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
	ret = init_ls_2("/Users/adpusel", l);
	if (ret
		|| l->array->length != 44
		|| strcmp("/Users/adpusel", l->path))
		ft_test_error("test_init_ls 1");
	ls_free(l);

	// test with good arg
	ret = init_ls_2("/Users/adpuselaoeu", l);
	if (!ret || l->array || strcmp("/Users/adpuselaoeu", l->path))
		ft_test_error("test_init_ls 2");
}

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

	init_ls_2("/Users/adpusel", l);
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
	ls_free(l);

	init_ls_2("/dev", l);
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

void main_test_2()
{
	helper_test();
	test_init_ls_2();
	test_ft_ls_max();
	test_ft_set_max();
	test_array_file_name();
	test_fill_file();
}