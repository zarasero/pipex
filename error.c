/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:58:26 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/09 15:58:28 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(t_pipex *p)
{
	if (p)
	{
		if (p->command1)
			free_map(p->command1);
		if (p->command2)
			free_map(p->command2);
		if (p->path_map)
			free_map(p->path_map);
	}
}

void	error_simple2(const char *message, char *dop, int status, t_pipex *p)
{
	write(2, "bash: ", 6);
	ft_putstr11(dop);
	write(2, ": ", 2);
	ft_putstr((char *)message);
	write(2, "\n", 1);
	ft_free(p);
	exit(status);
}

void	error_simple1(const char *message, char *dop, int status)
{
	write(2, "bash: ", 6);
	write(2, dop, ft_strlen(dop));
	write(2, ": ", 2);
	ft_putstr((char *)message);
	write(2, "\n", 1);
	exit(status);
}

void	ft_putstr11(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	error_sansexit(const char *message, char *dop)
{
	write(2, "bash: ", 6);
	ft_putstr11(dop);
	write(2, ": ", 2);
	ft_putstr((char *)message);
	write(2, "\n", 1);
}
