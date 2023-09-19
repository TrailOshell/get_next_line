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

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#ifndef	BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

//	get_next_line.c
char	*get_next_line(int fd);

//	get_next_line_utils.c

#endif
