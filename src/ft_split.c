/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjiang <hjiang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:08:30 by hjiang            #+#    #+#             */
/*   Updated: 2025/04/15 17:13:43 by hjiang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	count_word(char const *s, char c)
{
	unsigned int	x;
	unsigned int	count;

	x = 0;
	count = 0;
	while (s[x] != '\0')
	{
		if (s[x] != c && (s[x + 1] == c || s[x + 1] == '\0'))
			count++;
		x++;
	}
	return (count);
}

static char	*cpyletter(char const *s, char c)
{
	char			*tab;
	unsigned int	letter;
	unsigned int	a;

	letter = 0;
	a = 0;
	while (s[letter] != c && s[letter] != '\0')
		letter++;
	tab = malloc(sizeof(char) * (letter + 1));
	if (!tab)
		return (NULL);
	while (a < letter)
	{
		if (s[a] == c && s[a + 1] == c)
			break ;
		tab[a] = s[a];
		a++;
	}
	tab[a] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	n;
	unsigned int	x;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	n = count_word(s, c);
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (NULL);
	x = 0;
	i = 0;
	while (s[x] != '\0' && i < n)
	{
		while (s[x] == c && s[x] != '\0')
			x++;
		tab[i] = cpyletter(&s[x], c);
		if (tab[i] == NULL)
			return (ft_free(tab), NULL);
		x = x + ft_strlen(tab[i]);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
