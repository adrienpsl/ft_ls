#include <ft_ls.h>

int init_ls_2(char *path, t_ls_2 *l);
void ls_free(t_ls_2 *l);

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
	if (!ret || l->array || strcmp("/Users/adpusel", l->path))
		ft_test_error("test_init_ls 2");
}

void main_test_2()
{
	helper_test();
	test_init_ls_2();


}