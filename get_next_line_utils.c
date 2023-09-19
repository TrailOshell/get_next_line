/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:57:02 by tsomchan          #+#    #+#             */
/*   Updated: 2023/09/19 14:57:03 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char			*ptr;
	size_t			i;

	if (!s1)
		return (0);
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (i < n)
		ptr[i++] = *s1++;
	return (ptr);
}