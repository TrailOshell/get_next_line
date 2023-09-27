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
		free(tmp);
		// output_chars("line", line);
		*store = get_store(*store, index);
		// output_chars("*store", *store);
		return (line);
	}
	while (read_data)
	{
		// output_chars("*store", *store);
		read_data = read(fd, buffer, BUFFER_SIZE);
		if (read_data == -1)
			return (NULL);
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
	size_t	len;

	// output_chars("buffer", buffer);
	str = NULL;
	if (buffer && !*buffer)
		return (NULL);
	// printf("index = %zu\n", index);
	len = 0;
	if (buffer[index])	
		len = ft_strlen(buffer + index);
	// printf("len = %zu\n", len);
	if (!len)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (len)
		str = ft_substr(buffer, index, len + 1);
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
/*
char	*get_store(char *store, char *buffer)
{
	char	*trim1;
	char	*trim2;
	size_t	size1;
	size_t	size2;
	char	*str;
	size_t	i;

	printf("store =\"%s\"\n", store);
	size1 = 0;	
	if (trim1)
		trim1 = ft_strchr(store, '\n') + 1;
		// size1 = ft_strlen(trim1);
		// trim1 = ft_strlen(ft_strchr(store, '\n')) - 1;
	// printf("trim1 =\"%zu\"\n", trim1);
	printf("buffer =\"%s\"\n", buffer);
	trim2 = ft_strchr(buffer, '\n') + 1;
	size2 = 0;	
	if (trim2)
		size2 = ft_strlen(trim2);
		// trim2 = ft_strlen(ft_strchr(buffer, '\n')) - 1;
	// printf("trim2 =\"%zu\"\n", trim2);
	str = malloc(size1 + size2 + 1);
	// str = malloc(ft_strlen(trim1) + ft_strlen(trim2) + 1);
	if (!str)
		return (NULL);
	i = 0;	
	printf("str =\"%s\"\n", str);
	if (trim1)
	{
		// trim1 += trim1 + 1;
		while (*trim1)
			str[i++] = *(trim1++);
		printf("str1 =\"%s\"\n", str);
	}
	if (trim2)
	{
		// trim2 += trim2 + 1;
		while (*trim2)
			str[i++] = *(trim2++);
		printf("str2 =\"%s\"\n", str);
	}
	// while (*trim1)
	// 	str[i++] = *(trim1++);
	// while (*trim2)
	// 	str[i++] = *(trim2++);
	str[i] = '\0';
	printf("str =\"%s\"\n", str);
	return (str);

	// printf("buffer =\"%s\"\n", buffer);
	// tmp = *store;
	// *store = ft_strdup(trim);
	// free(tmp);
}
*/

// char	*cut_line(char *line)
// {
// 	char	*store;
// 	size_t	len;

// 	while (*line != '\n' && *line != '\0')
// 		line++;
// 	if (*line == '\n')
// 		line++;
// 	if (*line == '\0')
// 		return (NULL);
// 	len = ft_strlen(line);
// 	store = malloc(len + 1);
// 	if (!store)
// 		return (NULL);
// 	while (*line)
// 		*store++ = *line++;
// 	*store = '\0';
// 	store -= len;
// 	if (*store == '\0')
// 		free(store);
// 	*(line - len) = '\0';
// 	return (store);
// }

//	the mandatory function

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