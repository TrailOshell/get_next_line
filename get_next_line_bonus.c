/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:00:58 by tsomchan          #+#    #+#             */
/*   Updated: 2023/09/23 16:01:00 by tsomchan         ###   ########.fr       */
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
