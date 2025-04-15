/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjiang <hjiang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:27:53 by hjiang            #+#    #+#             */
/*   Updated: 2025/04/15 18:45:11 by hjiang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <aio.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	child1(char **av, int fd[2], char **envp, pid_t pid1);
void	child2(char **av, int fd[2], char **envp, pid_t pid2);

void	exec_cmd(char *av, char **envp);
char	*get_path(char *cmd, char **envp);

char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_cmd(char **cmd, char *path);
int		ft_strlen(const char *str);

char	**ft_split(char const *s, char c);
#endif
