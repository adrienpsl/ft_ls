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

#include <test.h>
#include <libft.test.h>
#include "ft_ls..h"

static int utils(char *av_str, char *result)
{
	(void)result;
	char **av = ft_strsplit(av_str, " ");

	ft_ls(av);

	ft_strsplit_free(&av);
//	if (lib_cmp_testbuff(result))
//		return (1);

	return (0);
}

void test_ft_ls()
{
	(void)utils;
	g_test = 0;
//	utils("-l /var/run/mDNSResponder /", "");
	utils("test_dir test_dir/fifo", "/test_dir");

}
