#include <stdio.h>
#include <ft_ls.h>

int main(int ac, char **av)
{
	t_ls ls;

	(void)ac;
	ft_bzero(&ls, sizeof(t_ls));
	ls$catch_options(av, (long*)&ls.options);

	test_ft_ls$main_test();

	return 0;
}