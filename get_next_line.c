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

char	*read_next_line(int fd, char *store)
{
	int		read_data;
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_data = 1;
	while (read_data)
	{
		read_data = read(fd, buffer, BUFFER_SIZE);
		if (read_data < 0)
			return (NULL);
		if (!read_data)
			break ;
		buffer[read_data] = '\0';
		if (!store)
			store = ft_strdup("");
		tmp = store;
		store = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (check_newline(buffer))
			break ;
	}
	free(buffer);
	return (store);
}

char	*cut_line(char *line)
{
	char	*store;
	size_t	len;

	len = ft_find_newline(line);
	while (*line != '\n' && *line != '\0')
		line++;
	if (*line == '\0' || *(line - (len) + 1) == '\0')
		return (NULL);
	*(line + 1) = '\0';	
	
	//	keep buffer
	len = ft_strlen(line);
	store = malloc(len + 1);
	if (!store)
		return (NULL);
	while (*line)
		*store++ = *line++;
	*store = '\0';
	store -= len;
	if (*store == '\0')
	{
		free(store);
		store = NULL;
	}
	return (store);
}

//	the mandatory function
char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0)
		return (NULL);
	line = read_next_line(fd, store);
	if (line)
		store = cut_line(line);
	// printf("store\t= \"%s\"\n", buffer);
	return (line);
}

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