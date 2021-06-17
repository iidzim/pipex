/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:09:35 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/17 20:00:11 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*p;
	int		size;

	i = 0;
	size = ft_strlen(str);
	p = (char *)malloc((size + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		p = (char *)malloc(1 * sizeof(char));
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (len-- > 0)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	*(p + i) = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, const char *s2)
{
	int		i;
	int		j;
	char	*p;
	int		size_s1;
	int		size_s2;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	size_s1 = ft_strlen((char *)s1);
	size_s2 = ft_strlen((char *)s2);
	p = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	i = -1;
	j = 0;
	if (p)
	{
		while (s1[++i] != '\0')
			p[i] = s1[i];
		while (s2[j])
			p[i++] = s2[j++];
		p[i] = '\0';
		return (p);
	}
	return (NULL);
}

char	*ft_joinchar(char *s, char c)
{
	int		i;
	char	*str;

	i = strlen(s);
	if (!(str = (char *)malloc(i + 2)))
		return (0);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = c;
	str[i + 1] = '\0';
	// free(s);
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i); 
}

// char	*ft_strcat(char *dst, char *src, size_t size)
// {
	// size_t	i;
	// size_t	size_dst;
	// size_t	size_src;

	// size_dst = ft_strlen(dst);
	// size_src = ft_strlen((char *)src);
	// if (size <= size_dst)
	// 	return (size + size_src);
	// i = 0;
	// while (src[i] != '\0' && (size - 1) > size_dst + i)
	// {
	// 	dst[size_dst + i] = src[i];
	// 	i++;
	// }
	// dst[size_dst + i] = '\0';
	// return (size_dst + size_src);
// }
