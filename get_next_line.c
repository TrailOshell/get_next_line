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
		while (str[i] != '\n' && answer[i] != '\0')
			i++;
		*index = i;
	}
	return (NULL);
}

char	*read_to_init(int *read_data, char *str, int fd, int i)
{
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	while (*read_data)
	{
		*read_data = read(fd, buffer, BUFFER_SIZE);
		// if (*read_data < 0)
			return (free_null(str, buffer, 1, i));
		if (!*number_read)
			break ;
		buffer[*read_data] = '\0';
		// if (!str)
			// str = ft_strdup("");
		tmp = ft_strjoin(str, buffer);
		free(str);
		str = tmp;
		free_null(str, NULL, );
		if (str[*i] == '\n')
			break ;
	}
	free(buffer);
	return (str);
}

//	the mandatory function
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*str;
	int			read_data;
	int			i;

	if (fd < 0)
		return (0);
	str = 0;
	if (buffer)
	{
		str = buffer;
		buffer = 0;
	}
	str = read_to_init(&read_data, str, fd, i);
	return (0);
}