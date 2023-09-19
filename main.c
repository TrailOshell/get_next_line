/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:41:26 by tsomchan          #+#    #+#             */
/*   Updated: 2023/09/19 15:41:27 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main()
{
	int	fd;
	char *ptr;


	fd = open("test",O_RDONLY);
	ptr = get_next_line(fd);
	//printf("%s",ptr);
	//free(ptr);
	while(ptr)
	{
		printf("%s",ptr);
		free(ptr);
		ptr = get_next_line(fd);
	}
	// ptr = get_next_line(fd);
	// printf("%s",ptr);
	// free(ptr);
	// ptr = get_next_line(fd);
	// printf("%s",ptr);
	// free(ptr);
	return(0);
}