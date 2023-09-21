/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:56:50 by tsomchan          #+#    #+#             */
/*   Updated: 2023/09/19 14:56:51 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//	get_next_line.c
char	*get_next_line(int fd);
char	*read_next_line(int fd, char *store, char *buffer);
char	*cut_line(char *line);
// char	*read_to_init(int *read_data, char *str, int fd, int *i);
// char	*free_null(char *str, char *buffer, int check, int *index);
// char	*free_null(char *str, char *buffer);
// char	*next_line(char *str, char **buffer, int i);

//	get_next_line_utils.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		check_newline(char *s);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// size_t	ft_find_newline(char *s);

#endif
