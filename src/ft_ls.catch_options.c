/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
# include "libft.h"

static void	usage(char c)
{
	ft_printf("ls: illegal option -- %c\n"
			  "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n",
			  c
	);
}

int			ls__catch_options(char ***p_av, t_options *option)
{
	int ret;

	ret = ftio__catch_option(*p_av, LS_OPTIONS, (long *)option, usage);
	if (option->no_group || option->numeric_group)
		option->long_format = 1;
	if (ret > 0)
		(*p_av) += ret;
	return (ret == -1 ? 1 : 0);
}
