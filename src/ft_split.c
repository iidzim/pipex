/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:07:05 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/17 20:00:22 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int			count_word(char const *s, char c)
{
	int		i;
	int		w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		else if (s[i] != c && s[i])
		{
			w++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (w);
}

static size_t		size_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void			clean(char **p, int c)
{
	while (c >= 0)
	{
		free(p[c]);
		c--;
	}
	free(p);
}

static char			*ft_next_word(const char *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

char				**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		nbw;
	char		**p;

	i = 0;
	if (!s)
		return (NULL);
	nbw = count_word((char *)s, c);
	p = (char **)malloc((nbw + 1) * sizeof(char*));
	if (p == NULL)
		return (NULL);
	while (i < nbw)
	{
		s = ft_next_word(s, c);
		p[i] = ft_substr(s, 0, size_word(s, c));
		if (p[i] == NULL)
		{
			clean(p, i);
			return (NULL);
		}
		i++;
		s += size_word(s, c);
	}
	p[nbw] = NULL;
	return (p);
}