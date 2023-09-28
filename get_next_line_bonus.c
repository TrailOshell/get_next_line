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

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*line;
	char		*tmp;
	size_t		index;

	line = NULL;
	if (fd < 0)
		return (NULL);
	index = 0;
	if (store[fd] && ft_strchr(store[fd], '\n'))
	{
		tmp = store[fd];
		line = join_line("", tmp, &index);
		store[fd] = get_store((store[fd])[index], store[fd] + index);
		return (free(tmp), line);
	}
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	line = read_next_line(fd, &store[fd], tmp);
	free(tmp);
	return (line);
}
