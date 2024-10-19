/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:44 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/10 16:38:09 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_trouve_allpath(t_pipex *p, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			p->path_all = *envp + 5;
			return (p->path_all);
		}
		envp++;
	}
	return (NULL);
}

char	*ft_trouve_path(t_pipex *p, char **command)
{
	char	*path;
	char	*joined_path;
	char	**path_map;

	path_map = p->path_map;
	while (*path_map)
	{
		path = *path_map;
		joined_path = ft_strjoin(path, "/");
		if (!joined_path)
			return (NULL);
		p->temp = ft_strjoin(joined_path, command[0]);
		free(joined_path);
		if (!p->temp)
			return (NULL);
		if (access(p->temp, F_OK) == 0)
			return (p->temp);
		free(p->temp);
		path_map++;
	}
	if (access(command[0], F_OK) == 0)
		return (command[0]);
	return (NULL);
}

void	child(char **argv, char **envp, t_pipex *p)
{
	char	*path;

	p->fd_in = open(argv[1], O_RDONLY);
	if (p->fd_in == -1 && errno == 13)
		error_simple2(strerror(errno), argv[1], 1, p);
	else if (p->fd_in == -1)
		error_simple2(strerror(errno), argv[1], errno, p);
	else
	{
		p->command1 = ft_split(argv[2], ' ');
		if (!p->command1 || !p->command1[0])
			error_simple22("command not found", " ", 0, p);
		path = ft_trouve_path(p, p->command1);
		if (path == NULL)
			error_simple22("command not found", argv[2], 127, p);
	}
	close(p->pip[0]);
	dup2(p->fd_in, STDIN_FILENO);
	dup2(p->pip[1], STDOUT_FILENO);
	close(p->pip[1]);
	close(p->fd_in);
	execve(path, p->command1, envp);
	error_simple22(strerror(errno), argv[3], errno, p);
}

void	parent(char **argv, char **envp, t_pipex *p)
{
	char	*path;

	p->fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->fd_out < 0)
	{
		error_simple2("Permission denied", argv[4], 1, p);
	}
	p->command2 = ft_split(argv[3], ' ');
	if (!p->command2 || !p->command2[0])
	{
		error_simple22("command not found", " ", 127, p);
	}
	path = ft_trouve_path(p, p->command2);
	if (path == NULL)
		error_simple22("command not found", argv[3], 127, p);
	close(p->pip[1]);
	dup2(p->pip[0], STDIN_FILENO);
	dup2(p->fd_out, STDOUT_FILENO);
	close(p->pip[0]);
	close(p->fd_out);
	execve(path, p->command2, envp);
	error_simple22(strerror(errno), argv[3], errno, p);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		status_code;

	status_code = 0;
	args_checker(argc);
	if (pipe(p.pip) < 0)
		error_simple1("Error pipe", " ", 1);
	initial(&p);
	if (ft_trouve_allpath(&p, envp) == NULL)
		error_simple1("PATH not found", " ", 1);
	p.path_map = ft_split(p.path_all, ':');
	p.pid = fork();
	if (p.pid == -1)
		error_simple1("Fork failed", "", 1);
	if (p.pid == 0)
	{
		child(argv, envp, &p);
	}
	else
	{
		parent(argv, envp, &p);
	}
	wait(NULL);
	ft_free(&p);
	return (status_code);
}*/

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	args_checker(argc);
	if (pipe(p.pip) < 0)
		error_simple1("Error pipe", " ", 1);
	initial(&p);
	if (ft_trouve_allpath(&p, envp) == NULL)
		error_simple1("PATH not found", " ", 1);
	p.path_map = ft_split(p.path_all, ':');
	p.pid1 = fork();
	if (p.pid1 == -1)
		error_simple1("Fork failed for child 1", "", 1);
	if (p.pid1 == 0)
		child(argv, envp, &p);
	p.pid2 = fork();
	if (p.pid2 == -1)
		error_simple1("Fork failed for child 2", "", 1);
	if (p.pid2 == 0)
		parent(argv, envp, &p);
	close(p.pip[0]);
	close(p.pip[1]);
	ft_wait(&p);
	ft_free(&p);
	return (p.exit_code);
}
