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
#include "testing/myft.h"
#include <stdio.h>

char	*join_line(char const *s1, char const *s2, size_t *index)
{
	char	*ptr;
	size_t	i;

	// printcolor("join_line()\n", "blue");
	if (!s1 || !s2)
		return (NULL);
	// output_chars("s1", (char *)s1);
	// output_chars("s2", (char *)s2);
	// printf("ptr size\t= %zu + %zu + 1\n", ft_strlen(s1), check_newline(s2));	
	ptr = malloc((ft_strlen(s1) + check_newline(s2) + 1));
	if (!ptr)
		return (NULL);
	*index = 0;
	i = 0;
	// printf("*s1\t= %c\n", *s1);
	// printf("*s2\t= %c\n", *s2);
	while (*s1 && *s1 != '\n')
		ptr[i++] = *s1++;
	if (*s1 == '\n')
		ptr[i++] = *s1++;
	while (s2[*index] && s2[*index] != '\n')
		ptr[i++] = s2[(*index)++];
	if (s2[*index] == '\n')
		ptr[i++] = s2[(*index)++];
	ptr[i] = '\0';
	// output_chars("ptr", (char *)ptr);
	// printcolor("join_line() END\n", "blue");
return (ptr);
}

char	*read_next_line(int fd, char **store, char *buffer)
{
	int		read_data;
	char	*tmp;
	char	*line;
	size_t	index;

	// output_chars("*store", *store);
	index = 0;
	read_data = 1;
	if (*store && ft_strchr(*store, '\n'))
	{
		tmp = *store;
		line = join_line("", tmp, &index);
		// output_chars("line", line);
		*store = get_store(*store, index);
		// output_chars("*store", *store);
		free(tmp);
		return (line);
	}
	while (read_data)
	{
		// output_chars("*store", *store);
		read_data = read(fd, buffer, BUFFER_SIZE);
		if (read_data == -1)
		{
			free(*store);
			return (NULL);
		}
		if (!read_data)
			break ;
		buffer[read_data] = '\0';
		if (!*store)
			*store = ft_strdup("");
		tmp = *store;
		// output_chars("tmp", tmp);
		// output_chars("buffer", buffer);
		*store = join_line(tmp, buffer, &index);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	line = *store;
	// output_chars("line", line);
	// output_chars("buffer", buffer);
	// printf("index\t= %zu\n", index);
	// printf("read_data\t= %d\n", read_data);
	if (read_data)
		*store = get_store(buffer, index);
	else
		*store = NULL;
	// output_chars("*store", *store);
	return (line);
}

char	*get_store(char *buffer, size_t index)
{
	char	*str;
	// size_t	len;

	// output_chars("buffer", buffer);
	str = NULL;
	// printf("index = %zu\n", index);
	// len = ft_strlen(buffer + index);
	// printf("len = %zu\n", len);
	if (buffer[index])
		str = ft_strdup(buffer + index);
		// str = ft_substr(buffer, index, len + 1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;
	char		*buffer;

	line = NULL;
	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_next_line(fd, &store, buffer);
	free(buffer);
	return (line);
}

/*
char	*read_next_line(int fd, char **store, char *buffer)
{
	int		read_data;
	char	*tmp;
	char	*line;

	// if (*store && ft_strchr(*store, '\n'))
		// return (join_line(*store, ""));
	// line = join_line(*store, "");
	line = (join_line(*store, ""));
	read_data = 1;
	while (read_data)
	{
		read_data = read(fd, buffer, BUFFER_SIZE);
		if (read_data <= -1)
			return (NULL);
		if (!read_data)
			break ;
		buffer[read_data] = '\0';
		if (!line)
			line = ft_strdup("");
		tmp = line;
		line = join_line(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	// if (!line)
		// line = join_line(*store, "");
	// printf("line =\"%s\"\n", line);
	tmp = *store;
	*store = get_store(tmp, buffer);
	printf("*store =\"%s\"\n", *store);
	if (tmp)
		free(tmp);
	return (line);
}
char	*get_store(char *store, char *buffer)
{
	char	*str;
	char	*trim;
	size_t	len;
	// size_t	i;

	printf("store =\"%s\"\n", store);
	printf("buffer =\"%s\"\n", buffer);
	trim = NULL;
	if (store)
	{
		trim = ft_strchr(store, '\n');
		if (!trim)
			return (NULL);
	}
	// printf("trim =\"%s\"\n", trim);
	if (trim)
		len = ft_strlen(trim);
	else
	{
		if (*buffer == 0)
			return (NULL);
		trim = ft_strchr(buffer, '\n');
		// printf("trim =\"%s\"\n", trim);
		if (trim)
			len = ft_strlen(trim);
		else
		{
			return (NULL);
			// len = ft_strlen(buffer);
			// trim = buffer;
		}
	}
	if (len == 1)
		return (NULL);
	printf("len =\"%zu\"\n", len);
	if (*trim && *trim + 1 != '\0')
		trim++;
	str = ft_substr(trim, 0, len);
	return (str);
}
*/