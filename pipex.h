/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:06:26 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/07 17:07:05 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		pip[2];
	int		status_code1;
	int		status_code2;
	int		exit_code;
	int		temp1;
	pid_t	pid1;
	pid_t	pid2;
	char	*path_all;
	char	**path_map;
	char	**command1;
	char	**command2;
	char	*temp;
}	t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

int		main(int argc, char **argv, char **envp);
void	initial(t_pipex *p);
char	*ft_trouve_allpath(t_pipex *p, char **envp);
void	child(char **argv, char **envp, t_pipex *p);
void	parent(char **argv, char **envp, t_pipex *p);
void	ft_wait(t_pipex *p);

void	ft_free(t_pipex *p);
void	free_map(char **str);
void	ft_putstr(char *str);
void	args_checker(int argc);
void	error_simple1(const char *message, char *dop, int status);
void	ft_putstr11(char *str);
void	error_simple2(const char *message, char *dop, int status, t_pipex *p);
void	error_sansexit(const char *message, char *dop);
char	*ft_trouve_path(t_pipex *p, char **command);
void	error_simple22(const char *message, char *dop, int status, t_pipex *p);
#endif