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

#include "get_next_line_bonus.h"

char	*join_line(char const *s1, char const *s2, size_t *index,
		size_t *l_size)
{
	char	*ptr;
	size_t	i;
	size_t	size1;

	if (!s1 || !s2)
		return (NULL);
	if (l_size && *l_size > 0)
		size1 = *l_size;
	else
		size1 = len_till_nl(s1);
	*l_size = size1 + len_till_nl(s2);
	ptr = malloc(*l_size + 1);
	if (!ptr)
		return (NULL);
	*index = 0;
	i = 0;
	while (*s1 && *s1 != '\n')
		ptr[i++] = *s1++;
	while (s2[*index] && s2[*index] != '\n')
		ptr[i++] = s2[(*index)++];
	if (s2[*index] == '\n')
		ptr[i++] = s2[(*index)++];
	ptr[i] = '\0';
	return (ptr);
}

void	get_store(char **store, int condition, char *section)
{
	if (condition == -1)
	{
		free(*store);
		*store = NULL;
	}
	else if (condition)
		*store = ft_strdup(section);
	else
		*store = NULL;
}

char	*read_next_line(int fd, char **store, char *buffer)
{
	int		rd_data;
	char	*tmp;
	char	*line;
	size_t	index;
	size_t	l_size;

	index = 0;
	l_size = 0;
	rd_data = read(fd, buffer, BUFFER_SIZE);
	while (rd_data > 0)
	{
		buffer[rd_data] = '\0';
		if (!*store)
			*store = ft_strdup("");
		tmp = *store;
		*store = join_line(tmp, buffer, &index, &l_size);
		free(tmp);
		if (index && buffer[index - 1] == '\n')
			break ;
		rd_data = read(fd, buffer, BUFFER_SIZE);
	}
	if (rd_data == -1)
		return (get_store(store, -1, NULL), NULL);
	line = *store;
	return (get_store(store, rd_data && buffer[index], buffer + index), line);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*line;
	char		*tmp;
	size_t		index;
	size_t		l_size;

	line = NULL;
	if (fd < 0)
		return (NULL);
	index = len_till_nl(store[fd]);
	l_size = 0;
	if (index && store[fd][index - 1] == '\n')
	{
		tmp = store[fd];
		line = join_line("", tmp, &index, &l_size);
		get_store(&(store[fd]), (store[fd])[index], store[fd] + index);
		return (free(tmp), line);
	}
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	line = read_next_line(fd, &store[fd], tmp);
	free(tmp);
	return (line);
}
