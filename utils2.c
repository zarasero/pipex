/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:57:36 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/18 14:57:47 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_wait(t_pipex *p)
{
	waitpid(p->pid1, &p->status_code1, 0);
	waitpid(p->pid2, &p->status_code2, 0);
	if (WIFEXITED(p->status_code2))
		p->exit_code = WEXITSTATUS(p->status_code2);
}

void	error_simple22(const char *message, char *dop, int status, t_pipex *p)
{
	ft_putstr11(dop);
	write(2, ": ", 2);
	ft_putstr((char *)message);
	write(2, "\n", 1);
	ft_free(p);
	exit(status);
}

/*void	error_simple33(t_pipex *p, char *argv)
{
	if (p->temp1 == 1)
		error_simple22("Command execution failed", argv, 1, p);
	else
	{
		ft_free(p);
		exit(127);
	}
}*/
