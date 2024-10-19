/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:06:15 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/14 15:06:19 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	write(2, str, i);
}

void	free_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	args_checker(int argc)
{
	if (argc != 5)
	{
		ft_putstr("bash: 5 arguments is required");
		write(2, "\n", 1);
		exit(1);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	initial(t_pipex *p)
{
	p->command1 = NULL;
	p->command2 = NULL;
	p->temp = NULL;
	p->status_code1 = 0;
	p->status_code2 = 0;
	p->exit_code = 0;
	p->temp1 = 1;
}
