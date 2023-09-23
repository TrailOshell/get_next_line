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

#include "../get_next_line.h"

// void	check_newline(char *str);
// {
// 	while(*str && *str != '\n')
// 		str++;
// 	if (*str == '\n')
// 		return (1);
// 	return (0);
// }

static int	count = 1;

void	print_chars(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			printf("\\n");
		else
			printf("%c", *str);
		str++;
	}
}

void	print_line(char *str)
{
	// printf("-----------------------------------------\n");
	printf("[%d] next line is --> \"", count++);
	print_chars(str);
	if (!check_newline(str))
		printf("\" (no '\\n')\n");
	else
		printf("\"\n");
	// printf("-----------------------------------------\n");
}

void	test_gnl(char *test)
{
	int			fd;
	char		*ptr;

	count = 1;
	printf("/////////////////////////////////////////\n");
	printf("test file\t= %s\n", test);
	fd = open(test, O_RDONLY);
	ptr = get_next_line(fd);
	while (ptr)
	{
		print_line(ptr);
		free(ptr);
		ptr = get_next_line(fd);
	}
	free(ptr);
	printf("-----------------------------------------\n");
}

int	main()
{
	printf("BUFFER_SIZE\t= %d\n", BUFFER_SIZE);
	test_gnl("giant_line.txt");
	test_gnl("giant_line_nl.txt");
	test_gnl("text");
	test_gnl("empty.txt");
	test_gnl("1char.txt");
	test_gnl("one_line_no_nl.txt");
	test_gnl("only_nl.txt");
	test_gnl("multiple_nl.txt");
	test_gnl("variable_nls.txt");
	test_gnl("lines_around_10.txt");
	test_gnl("read_error.txt");
	return(0);
}

/*
	fd = open("multiple_nl.txt",O_RDONLY);
	fd = open("only_nl.txt",O_RDONLY);
	fd = open("text",O_RDONLY);
	fd = open("lines_around_10.txt",O_RDONLY);
*/
/*
	ptr = get_next_line(fd);
	while (ptr)
	{
		print_line(ptr);
		free(ptr);
		ptr = get_next_line(fd);
	}
*/
/*
	ptr = get_next_line(fd);
	print_line(ptr);
	free(ptr);
	ptr = get_next_line(fd);
	print_line(ptr);
	free(ptr);
*/
	/*
		ptr = get_next_line(fd);
		printf("initial ptr\t=%s",ptr);
		printf("----------------------\n");
		free(ptr);
	*/