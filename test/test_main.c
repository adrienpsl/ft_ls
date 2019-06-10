//# include "../src/main.c"

#include "ft_ls.h"

int init_ls(t_ft_ls *l, int ac, char **av);
int ft_ls_parse_options(t_ft_ls *l);
int ft_ls_parse_argv(t_ft_ls *l);


void utils_build_array_str(char **s, t_array **array, int size)
{
	int i = 0;
	void *tmp;
	if (s == NULL)
		return;
	ft_array_new(array, size, sizeof(char *));

	while (i < size)
	{
		tmp = ft_array_next_el(*array);
		ft_mem_copy(tmp, s[i], sizeof(char *));
		i++;
	}
}

void test_init_ls(t_ft_ls *l, int ac, char **av)
{
	init_ls(l, ac, av);
}

void u_test_ft_ls_parse_options(char **options_str, int size, long res_option, int ret, int stop)
{
	static int nb = 0;
	int intern_ret;
	(void) intern_ret;
	t_ft_ls ls;
	t_ft_ls *l = &ls;

	init_ls(l, size, options_str);
	intern_ret = ft_ls_parse_options(l);
	if (
			l->options != res_option ||
			intern_ret != ret ||
			l->i != stop
			)

		ft_print_error("test_ft_ls_parse_option", nb);
	nb++;
}

void test_ft_ls_parse_options()
{
	char *tab1[10] = {"name"};
	u_test_ft_ls_parse_options(tab1, 1, 0, 0, 1);

	char *tab2[10] = {"name", "-o"};
	u_test_ft_ls_parse_options(tab2, 2, 0, -1, 1);

	char *tab3[10] = {"name", "-llRRTT111"};
	u_test_ft_ls_parse_options(tab3, 2,
							   (FT_LS_O_R | FT_LS_O_T | FT_LS_O_l | FT_LS_O_1),
							   0, 2);

	char *tab4[10] = {"name", "-llRRTT111", "-llRRTT111e"};
	u_test_ft_ls_parse_options(tab4, 3,
							   (FT_LS_O_R | FT_LS_O_T | FT_LS_O_l | FT_LS_O_1),
							   -1, 2);

	char *tab5[10] = {"name", "-", "--", "---"};
	u_test_ft_ls_parse_options(tab5, 6, 0, 0, 2);

	char *tab6[10] = {"name", "--", "--", "---"};
	u_test_ft_ls_parse_options(tab6, 6, 0, 0, 2);

	char *tab7[10] = {"name", "-a", "--", "---"};
	u_test_ft_ls_parse_options(tab7, 6, FT_LS_O_a, 0, 3);

	char *tab8[10] = {"name", "-a", "--a", "---"};
	u_test_ft_ls_parse_options(tab8, 6, FT_LS_O_a, -1, 3);
}

void u_test_ft_ls_parse_argv(char **options_str,
							 int size,
							 long res_option,
							 int ret,
							 int stop,
							 char **res_array,
							 int res_array_cmp)
{
	static int nb = 0;
	int intern_ret;
	t_ft_ls ls;
	t_ft_ls *l = &ls;
	t_array *array = NULL;

	utils_build_array_str(res_array, &array, size - 1);

	init_ls(l, size, options_str);
	intern_ret = ft_ls_parse_argv(l);
	if (
			l->options != res_option ||
			intern_ret != ret ||
			l->i != stop
			|| ft_array_cmp(array, l->argv, NULL, STRING_MODE) != res_array_cmp
			)
		ft_print_error("test_ft_ls_parse_argv :", nb);

	ft_array_func(array, ft_array_print_str, 0);
	printf("\n");
	ft_array_func(l->argv, ft_array_print_str, 0);
	printf("\n");
	if (array)
		free(array);
	free(l->argv);
	free(l->buff);
	nb++;
}

void test_ft_ls_parse_argv()
{
	char *tab1[10] = {"name"};
	u_test_ft_ls_parse_argv(tab1, 1, 0, 0, 1, NULL, 1);

	char *tab2[10] = {"name", "a", "b", "c"};
	char *tab_2[10] = {"a", "b", "c"};
	u_test_ft_ls_parse_argv(tab2, 4, 0, 0, 4, tab_2, 0);

	char *tab3[20] = {"name", "c", "b", "a", "e", "aoue", "aou"};
	char *tab_3[20] = {"a", "aou", "aoue", "b", "c", "e"};
	u_test_ft_ls_parse_argv(tab3, 7, 0, 0, 7, tab_3, 0);

}

typedef struct testop
{
	char **options_str;
	int size_option;
	long res_option;
	int ret;
	int stop;
	char **res_array;
	int res_array_cmp;
	int option_number;

} t_test_ft;

void u_test_ft_ls_parse_option_argv(t_test_ft *test)
{
	static int nb = 0;
	int ret_option;
	int ret_argv;
	t_ft_ls ls;
	t_ft_ls *l = &ls;
	t_array *array = NULL;

	utils_build_array_str(test->res_array, &array, test->size_option - test->option_number);

	init_ls(l, test->size_option, test->options_str);
	ret_option = ft_ls_parse_options(l);
	ret_argv = ft_ls_parse_argv(l);
	if (
			l->options != test->res_option ||
			ret_argv != test->ret ||
			ret_option != test->ret ||
			l->i != test->stop
			|| ft_array_cmp(array, l->argv, NULL, STRING_MODE) != test->res_array_cmp
			)
		ft_print_error("test_ft_ls_parse_argv :", nb);

	ft_array_func(array, ft_array_print_str, 0);
	printf("\n");
	ft_array_func(l->argv, ft_array_print_str, 0);
	printf("\n");
	if (array)
		free(array);
	free(l->argv);
	free(l->buff);
	nb++;
}


void test_main_main()
{
/*	t_ft_ls l;
	(void) l;

	// test init
	test_init_ls(&l, 0, NULL);*/

//	test_ft_ls_parse_options();
//	test_ft_ls_parse_argv();



//	char *tab3[20] = {"name", "-a", "-R", "c", "b", "a", "e", "aoue", "aou"};
//	char *tab_3[20] = {"a", "aou", "aoue", "b", "c", "e"};
//
//	t_test_ft t = {tab3, 9, (FT_LS_O_R | FT_LS_O_a), 0, 9, tab_3, 0, 3};
//	u_test_ft_ls_parse_option_argv(&t);

	char *tab4[20] = {"name", "-", "-R", "c", "b", "a", "e", "aoue", "aou"};
	char *tab_4[20] = {"-R", "a", "aou", "aoue", "b", "c", "e"};

	t_test_ft t4 = {tab4, 9, 0, 0, 9, tab_4, 0, 2};
	u_test_ft_ls_parse_option_argv(&t4);


}
