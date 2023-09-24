/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:48:02 by tsomchan          #+#    #+#             */
/*   Updated: 2023/09/19 14:48:03 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_next_line(int fd, char *store, char *buffer)
{
	int		read_data;
	char	*tmp;

	read_data = 1;
	while (read_data)
	{
		read_data = read(fd, buffer, BUFFER_SIZE);
		if (read_data <= -1)
			return (NULL);
		if (!read_data)
			break ;
		buffer[read_data] = '\0';
		if (!store)
			store = ft_strdup("");
		tmp = store;
		store = ft_strjoin(tmp, buffer);
		free(tmp);
		if (check_newline(buffer))
			break ;
	}
	return (store);
}

char	*cut_line(char *line)
{
	char	*store;
	size_t	len;

	while (*line != '\n' && *line != '\0')
		line++;
	if (*line == '\n')
		line++;
	if (*line == '\0')
		return (NULL);
	len = ft_strlen(line);
	store = malloc(len + 1);
	if (!store)
		return (NULL);
	while (*line)
		*store++ = *line++;
	*store = '\0';
	store -= len;
	if (*store == '\0')
		free(store);
	*(line - len) = '\0';
	return (store);
}

//	the mandatory function
char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;
	char		*buffer;

	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_next_line(fd, store, buffer);
	free(buffer);
	if (line)
		store = cut_line(line);
	else
	{
		free(store);
		store = NULL;
	}
	return (line);
}

/*
	// if (*line == '\0' || *(line - (len) + 1) == '\0')
	// printf("store\t= \"%s\"\n", store);
	// printf("line\t= \"%s\"\n", line);
	// printf("store\t= \"%s\"\n", buffer);
*/
/*
char	*read_next_line(int read_data, char *str, int fd)
{
	char	*buffer;
	char	*ptr;
	int		i;
	int		len;

	buffer = malloc(BUFFER_SIZE + 1);
	while (read_data)
	{
		read_data = read(fd, buffer, BUFFER_SIZE);
		if (read_data < 0)
			return (free_null(str, buffer, 1, &i));
		if (!read_data)
			return (free_null(str, buffer, 1, &i));
		buffer[read_data] = '\0';
		if (!str)
			str = ft_strdup("");
		i = 0;
		len = ft_find_newline(buffer);
		ptr = str;
		str = malloc(ft_strlen(str) + len + 1);
		if (!ptr)
			return (NULL);
		while (*ptr)
			str[i++] = *ptr++;
		free(ptr);
		while (*buffer && *buffer != '\n')
			str[i++] = *buffer++;
		if (*buffer == '\n')
			str[i++] = '\n';
		str[i] = '\0';
		free(buffer - len + 1);
		if (str[i - 1] == '\n')
			break;
	}
	return (str);
}
*/

/*
	char	*free_null(char *str, char *buffer, int check, int *index)
	{
		int	i;

		i = 0;
		if (check)
		{
			free(str);
			free(buffer);
		}
		else
		{
			while (str[i] != '\n' && str[i] != '\0')
				i++;
			*index = i;
		}
		return (NULL);
	}
*/