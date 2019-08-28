#include <ft_ls.h>

int main(int ac, char **av)
{
	//	t_ls ls;

	(void)ac;
	(void)av;
	//	ft_bzero(&ls, sizeof(t_ls));
	//	ls__catch_options(&av, (long*)&ls.options);

	//	test_ft_ls$main_test();
	ft_ls(av + 1);

	return 0;
}