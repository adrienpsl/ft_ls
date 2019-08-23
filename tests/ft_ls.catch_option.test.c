
#include <ft_strsplit.h>
#include <ft_ls..h>
#include <test.h>
#include <libft.test.h>

static int utils(char *av_str, char *result_str, long result_option, int retour)
{
	char **split_av = ft_strsplit(av_str, " ");
	char **split_result = ft_strsplit(result_str, " ");
	char **av = split_av;
	long option = 0;

	int ret = ls$catch_options(&av, (t_ls_options*)&option);

	if (
		ft_strsplit_cmp(split_result, av)
		|| option != result_option
		|| ret != retour
		)
		return (-1);

	ft_strsplit_free(&split_av);
	ft_strsplit_free(&split_result);
	return (0);
}

void test_ls$catch_option()
{
	// error
	{
		g_test = 1;

		if (utils("---", "---", (long)0, 1))
			log_test(0)
		if (lib_cmp_testbuff("ls: illegal option -- -\n"
							 "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n"))
			log_test(0)

		if (utils("--a -z", "--a -z", (long)1, 1))
			log_test(0)
		if (lib_cmp_testbuff("ls: illegal option -- z\n"
							 "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n"))
			log_test(0)
	}

	g_test = 0;
	g_log = TRACE;

	// simple test
	{
		if (utils("", "", (long)0, 0))
			log_test(0)

		if (utils("-", "-", (long)0, 0))
			log_test(0)

		if (utils("-- -", "-", (long)0, 0))
			log_test(0)

		if (utils("-a -", "-", (long)1, 0))
			log_test(0)

		if (utils("-l -llllll --lllllllllll -", "-", (long)4, 0))
			log_test(0)

		if (utils("-l -llllaaaaaaall -a --lllllllllll -", "-", (long)5, 0))
			log_test(0)
	}

	// test with all
	{
		if (utils("-l -a -R", "", (long)7, 0))
			log_test(0)
	}

}