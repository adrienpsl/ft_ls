
#include <ft_libft_struct.h>
#include "ft_ls.h"

void main_test_2();

int parsing_options(char *av, long *p_options)
{
	static char *options = "RlartncSguT1";

	if (ft_io_catch_options(av, options, p_options))
	{
		ft_printf("usage : ft_ls -[%s]", options);
		return (-1);
	}
	return (0);
}


int test_file(char *path, int options)
{
	t_buff *buff;
	t_ls_2 ls;
	t_file file;

	if (lstat(path, &ls.fs) || ft_buffer_new(&buff, 35000, 1))
		return (1);
	if (S_ISDIR(ls.fs.st_mode))
		ft_all(path, options, buff, path);
	else
	{
		ls.buff = buff;
		ls.options = options;
		ft_mem_copy(ls.path, path, STRING_MODE);
		if (options & FT_LS_O_l)
		{
			ls.f = &file;
			ft_mem_copy(file.name, path, STRING_MODE);
			print_stats(&ls);
		}
		else
			ft_sprintf(buff, "%s\n", path);
	}
	ft_buffer_clean(buff);
	ft_buffer_free(&buff);
	return (0);
}

int main(int ac, char **av)
{
	static int i = 1;
	static long option = 0;
	static int is_path = 0;

	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (parsing_options(av[i] + 1, &option))
				return (EXIT_FAILURE);
		}
		else
		{
			if (test_file(av[i], option))
				print_err(av[i]);
			is_path = 1;
		}
		i++;
	}

	if (is_path == 0)
		test_file(".", option);


//	main_test_2();

	// si option >
	//  bad option

	// si plusieur option

	// si pas d'argument

	// si argv is file

	// si arvg is directory

	return 0;
}


