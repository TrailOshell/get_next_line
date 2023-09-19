/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:57:02 by tsomchan          #+#    #+#             */
/*   Updated: 2023/09/19 14:57:03 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char			*ptr;
	size_t			i;

	if (!s1)
		return (NULL);
	ptr = malloc((ft_strlen(s1) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s1)
		ptr[i++] = *s1++;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s1)
		ptr[i++] = *s1++;
	while (*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	char	*src;

	if (!s)
		return (0);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	sub = malloc(len + 1);
	if (!sub)
		return (0);
	src = (char *)(s + start);
	i = 0;
	if (len)
	{
		while (i < len - 1 && *src)
			sub[i++] = *src++;
		sub[i] = '\0';
	}
	return (sub);
}

/*	ft_strjoin
	// size1 = ft_strlen(s1);
	// size2 = ft_strlen(s2);
	// ptr = malloc(sizeof(char) * (size1 + size2 + 1));
		// ft_strlcpy(ptr, s1, size1 + 1);
		// while (i < size1 && *s1)
		// ft_strlcat(ptr, s2, ft_strlen(ptr) + size2 + 1);
		// while (i < size1 + size2 - 1 && *s2)
*/

/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (NULL);
	// ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	size1 = 0;
	size2 = 0;
	if (*s1)
		size1 = ft_strlen(s1);
	if (*s2)
		size2 = ft_strlen(s2);
	ptr = malloc((size1 + size2 + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	// while (*s1)
	while (i < size1 - 1 && *s1)
		ptr[i++] = *s1++;
	// while (*s2)
	while (i < size2 - 1 && *s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}
*/