/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjiang <hjiang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:38:55 by hjiang            #+#    #+#             */
/*   Updated: 2025/04/18 17:00:33 by hjiang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*find_path(char **paths, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (find_path(paths, cmd));
}

void	exec_cmd(char *av, char **envp)
{
	char	*path;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(av, ' ');
	if (access(cmd[0], F_OK | X_OK) == 0)
		path = cmd[0];
	else
		path = get_path(cmd[0], envp);
	if (!path)
	{
		free_cmd(cmd, path);
		write(2, "Error: Path no founded\n", 23);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_cmd(cmd, path);
		write(2, "Error: execve failed\n", 21);
		exit(EXIT_FAILURE);
	}
	free_cmd(cmd, path);
}
