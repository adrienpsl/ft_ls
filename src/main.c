
#include <ft_libft_struct.h>
#include "ft_ls.h"

void main_test_2();

int parsing_options(char *av, t_ls *l)
{
	static char *options = "RlartncSguT1";

	av++;
	if (*av)
	{
		l->option_catched = 1;
		return (0);
	}
	if (av[0] == '-')
		av += 1;
	if (!*av)
	{
		l->i++;
		l->option_catched = 1;
		return (0);
	}
	if (ft_io_catch_options(av, options, &l->options))
	{
		ft_printf("ls : illegal option -", options);
		ft_putchar_fd(*options, 1);
		ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] "
				  "[file ...]", options);
		return (-1);
	}
	return (1);
}

int test_file(char *path, t_ls *l)
{
	t_file file;

	ft_mem_set(&file, 0, sizeof(t_file));
	if (stat(path, &l->fs) && lstat(path, &l->fs))
		return (1);
	if (S_ISDIR(l->fs.st_mode))
		ft_all(path, l->options, l->buff, path);
	else
	{
		if (lstat(path, &l->fs))
			return (-1);
		ft_mem_copy(l->path, path, STRING_MODE);
		if (l->options & FT_LS_O_l)
		{
			l->f = &file;
			ft_mem_copy(l->f->name, path, STRING_MODE);
			print_stats(l);
		}
		else
			ft_sprintf(l->buff, "%s\n", path);
	}
	return (0);
}

// ici je veux quoi ? je veux avancer sur

// && ((av[ls.i][0] == '-' && av[ls.i][1])
//				|| (av[ls.i][0] == '-' && av[ls.i][1] == '-' && av[ls.i][2])))


// je dois loop sur les aguments
// - > coupe la prise d'arguments
// -- pass les argument
int main(int ac, char **av)
{
	t_ls ls;
	t_ft_ls l;

	ls.i = -1;
	ft_mem_set(&ls, 0, sizeof(t_ls));
	if (ft_buffer_new(&ls.buff, 35000, 1))
		return (EXIT_FAILURE);
	while (++ls.i < ac)
	{
		if (!ls.option_catched && av[ls.i][0] == '-')
		{
			if (parsing_options(av[ls.i], &ls) == -1)
				break;
		}
		else
			ls.option_catched = 1;
		if (ls.option_catched && ls.i < ac)
		{
			if ((ac - ls.i) > 1)
				ls.options |= FT_LS_O_M;
			if (test_file(av[ls.i], &ls))
				print_err(av[ls.i]);
			ls.is_path = 1;
		}
	}
	if (ls.is_path == 0)
		test_file(".", &ls);
	(ft_buffer_clean(ls.buff) || ft_buffer_free(&ls.buff));
	// TODO : free ls here
	return 0;
}

