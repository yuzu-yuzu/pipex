/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjiang <hjiang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:28:02 by hjiang            #+#    #+#             */
/*   Updated: 2025/04/18 15:31:49 by hjiang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(char **av, int fd[2], char **envp, int filein)
{
	if (dup2(filein, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		write(2, "Error: child1 dup2 failed", 25);
	close(filein);
	close(fd[0]);
	close(fd[1]);
	if (av[2][0] == '\0')
	{
		write(2, "Error: void argument\n", 21);
		exit(EXIT_FAILURE);
	}
	exec_cmd(av[2], envp);
}

void	child2(char **av, int fd[2], char **envp, int fileout)
{
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fileout, STDOUT_FILENO) == -1)
		write(2, "Error: child2 dup2 failed", 25);
	close(fileout);
	close(fd[0]);
	close(fd[1]);
	if (av[3][0] == '\0')
	{
		write(2, "Error: void argument\n", 21);
		exit(EXIT_FAILURE);
	}
	exec_cmd(av[3], envp);
}

static void	create_child1(char **av, int fd[2], char **envp)
{
	pid_t	pid1;
	int		filein;

	filein = open(av[1], O_RDONLY, 0000);
	if (filein == -1)
	{
		write(2, "Error: Open filein failed\n", 26);
		close(filein);
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	pid1 = fork();
	if (pid1 == -1)
		write(2, "Error: fork pid1 failed\n", 23);
	if (pid1 == 0)
		child1(av, fd, envp, filein);
	else
		close(filein);
}

static void	create_child2(char **av, int fd[2], char **envp)
{
	pid_t	pid2;
	int		fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		write(2, "Error: Open fileout failed\n", 26);
		close(fileout);
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == -1)
		write(2, "Error: fork pid2 failed\n", 23);
	if (pid2 == 0)
		child2(av, fd, envp, fileout);
	else
		close(fileout);
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
