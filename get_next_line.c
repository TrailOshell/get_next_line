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

	if (!s1 || !s2)
		return (NULL);
	ptr = malloc((ft_strlen(s1) + len_till_nl(s2) + 1));
	if (!ptr)
		return (NULL);
	*index = 0;
	i = 0;
	while (*s1 && *s1 != '\n')
		ptr[i++] = *s1++;
	if (*s1 == '\n')
		ptr[i++] = *s1++;
	while (s2[*index] && s2[*index] != '\n')
		ptr[i++] = s2[(*index)++];
	if (s2[*index] == '\n')
		ptr[i++] = s2[(*index)++];
	ptr[i] = '\0';
	return (ptr);
}
/* joinline()
	// printcolor("join_line()\n", "blue");
	// output_chars("s1", (char *)s1);
	// output_chars("s2", (char *)s2);
	// printf("ptr size\t= %zu + %zu + 1\n", ft_strlen(s1), len_till_nl(s2));	
	// printf("*s1\t= %c\n", *s1);
	// printf("*s2\t= %c\n", *s2);
	// output_chars("ptr", (char *)ptr);
	// printcolor("join_line() END\n", "blue");
*/

char	*get_store(int condition, char *section)
{
	if (condition)
		return (ft_strdup(section));
	else
		return (NULL);
}

char	*read_next_line(int fd, char **store, char *buffer)
{
	int		rd_data;
	char	*tmp;
	char	*line;
	size_t	index;

	index = 0;
	rd_data = 1;
	while (rd_data)
	{
		rd_data = read(fd, buffer, BUFFER_SIZE);
		if (rd_data == -1)
			return (free(*store), *store = NULL, NULL);
		if (!rd_data)
			break ;
		buffer[rd_data] = '\0';
		if (!*store)
			*store = ft_strdup("");
		tmp = *store;
		*store = join_line(tmp, buffer, &index);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	line = *store;
	return (*store = get_store(rd_data && buffer[index], buffer + index), line);
}
/* read_next_line()
	// output_chars("*store", *store);
		// output_chars("line", line);
			// *store = get_store(*store, index);
		// output_chars("*store", *store);
		// output_chars("*store", *store);
		// output_chars("tmp", tmp);
		// output_chars("buffer", buffer);
	// output_chars("line", line);
	// output_chars("buffer", buffer);
	// printf("index\t= %zu\n", index);
	// printf("read_data\t= %d\n", read_data);
		// *store = get_store(buffer, index);
	// output_chars("*store", *store);
*/

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;
	char		*tmp;
	size_t		index;

	line = NULL;
	if (fd < 0)
		return (NULL);
	index = 0;
	if (store && ft_strchr(store, '\n'))
	{
		tmp = store;
		line = join_line("", tmp, &index);
		store = get_store((store)[index], store + index);
		return (free(tmp), line);
	}
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	line = read_next_line(fd, &store, tmp);
	free(tmp);
	return (line);
}
