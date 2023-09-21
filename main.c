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

void	print_line(char *ptr)
{
	printf("--------------------------\n");
	printf("next line is\t--> %s",ptr);
	printf("--------------------------\n");
}

int	main()
{
	int	fd;
	char *ptr;

	printf("BUFFER_SIZE\t= %d\n", BUFFER_SIZE);
	fd = open("text",O_RDONLY);
	// while(ptr)
	// {
	// 	printf("get line -> %s",ptr);
	// 	free(ptr);
	// 	ptr = get_next_line(fd);
	// }
	ptr = get_next_line(fd);
	print_line(ptr);
	free(ptr);
	ptr = get_next_line(fd);
	print_line(ptr);
	free(ptr);
	return(0);
}

	/*
		ptr = get_next_line(fd);
		printf("initial ptr\t=%s",ptr);
		printf("----------------------\n");
		free(ptr);
	*/