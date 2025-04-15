/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjiang <hjiang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:28:02 by hjiang            #+#    #+#             */
/*   Updated: 2025/04/15 18:28:00 by hjiang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(char **av, int fd[2], char **envp, pid_t pid1)
{
	int	filein;

	if (pid1 == 0)
	{
		filein = open(av[1], O_RDONLY, 0777);
		if (filein == -1)
		{
			write(2, "Error: Open filein failed\n", 26);
			close(fd[0]);
			close(fd[1]);
			exit(EXIT_FAILURE);
		}
		dup2(filein, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_cmd(av[2], envp);
	}
}

void	child2(char **av, int fd[2], char **envp, pid_t pid2)
{
	int	fileout;

	if (pid2 == 0)
	{
		fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fileout == -1)
		{
			write(2, "Error: Open filein failed\n", 26);
			close(fd[0]);
			close(fd[1]);
			exit(EXIT_FAILURE);
		}
		dup2(fd[0], STDIN_FILENO);
		dup2(fileout, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_cmd(av[3], envp);
	}
}

static void	create_child1(char **av, int fd[2], char **envp)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
		write(2, "Error: fork pid1 failed\n", 23);
	child1(av, fd, envp, pid1);
}

static void	create_child2(char **av, int fd[2], char **envp)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		write(2, "Error: fork pid2 failed\n", 23);
	child2(av, fd, envp, pid2);
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];

	if (ac != 5)
	{
		write(2, "Error: argument's number\n", 25);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		exit(EXIT_FAILURE);
	}
	create_child1(av, fd, envp);
	create_child2(av, fd, envp);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
