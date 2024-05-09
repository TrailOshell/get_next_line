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
//#include "testing/myft.h"

char	*join_line(char const *s1, char const *s2, size_t *l_len, size_t *b_nl)
{
	char	*ptr;
	size_t	i;
	size_t	size1;

	if (!s1 || !s2)
		return (NULL);
	size1 = *l_len;
	if (!size1)
		size1 = len_till_nl(s1);
	*l_len = size1 + len_till_nl(s2);
	ptr = malloc(*l_len + 1);
	if (!ptr)
		return (NULL);
	*b_nl = 0;
	i = 0;
	while (*s1 && *s1 != '\n')
		ptr[i++] = *s1++;
	if (*s1 == '\n')
		ptr[i++] = *s1++;
	while (s2[*b_nl] && s2[*b_nl] != '\n')
		ptr[i++] = s2[(*b_nl)++];
	if (s2[*b_nl] == '\n')
		ptr[i++] = s2[(*b_nl)++];
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

char	*read_next_line(int fd, char **store, char *buffer, size_t l_len)
{
	int		rd_data;
	char	*tmp;
	char	*line;
	size_t	b_nl;

	b_nl = 0;
	rd_data = read(fd, buffer, BUFFER_SIZE);
	while (rd_data > 0)
	{
		buffer[rd_data] = '\0';
		if (!*store)
			*store = ft_strdup("");
		tmp = *store;
		*store = join_line(tmp, buffer, &l_len, &b_nl);
		free(tmp);
		if (*store && (*store)[l_len - 1] == '\n')
			break ;
		rd_data = read(fd, buffer, BUFFER_SIZE);
	}
	if (rd_data == -1)
		return (get_store(store, -1, NULL), NULL);
	line = *store;
	return (get_store(store, rd_data && buffer[b_nl], buffer + b_nl), line);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*tmp;
	char		*line;
	size_t		l_len;
	size_t		b_nl;

	if (fd < 0)
		return (NULL);
	b_nl = 0;
	l_len = len_till_nl(store);
	if (store && store[l_len - 1] == '\n')
	{
		tmp = store;
		line = join_line(tmp, "", &l_len, &b_nl);
		get_store(&store, (store)[l_len], store + l_len);
		return (free(tmp), line);
	}
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	line = read_next_line(fd, &store, tmp, l_len);
	free(tmp);
	return (line);
}

/*	trying to optimize BUFFER_SIZE == 1 speed
char	*b_to_arr(int fd, char *buffer, char *arr)
{
	int		rd_data;
	int		i;

	i = 0;
	rd_data = 1;
	while (rd_data > 0 && i < 10)
	{
		(arr)[i++] = *buffer;
		if (*buffer == '\n')
			break;
		rd_data = read(fd, buffer, BUFFER_SIZE);
	}
	arr[i] = '\0';	
	return (arr);
}
	// if (BUFFER_SIZE == 1)
	// 	arr = malloc(10 + 1);
		// if (BUFFER_SIZE == 1)
		// 	*store = join_line(tmp, b_to_arr(fd, buffer, arr), &l_len, &b_nl);
		// else
		// 	*store = join_line(tmp, buffer, &l_len, &b_nl);
	// if (BUFFER_SIZE == 1)
	// 	return (free(arr), get_store(store, 0, NULL), line);
*/
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