/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:38:24 by mlagniez          #+#    #+#             */
/*   Updated: 2025/06/24 15:55:48 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd, int *check)
{
	char		**p_ret;
	char		*ret;
	char		*p_tail;
	static char	tail[1024][BUFFER_SIZE + 1];

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	if (read(fd, 0, 0) == -1)
		return (tail[fd][0] = 0, NULL);
	p_tail = NULL;
	ret = malloc(sizeof(char) * 1);
	if (!(ret))
		return (*check = 0, tail[fd][0] = 0, NULL);
	*ret = 0;
	p_ret = &ret;
	if (tail[0] && !update(p_ret, tail[fd]))
		return (*check = 0, free(ret), tail[fd][0] = 0, NULL);
	if (is_end(*p_ret))
		return (*p_ret);
	if (!read_through(fd, p_ret, &p_tail))
		return (*check = 0, free(*p_ret), NULL);
	ft_strlcpy_gnl(tail[fd], p_tail, BUFFER_SIZE + 1);
	return (free(p_tail), *p_ret);
}

int	read_through(int fd, char **p_ret, char **p_tail)
{
	char	*buffer;
	int		c;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	*p_tail = buffer;
	c = 1;
	while (c)
	{
		c = read(fd, buffer, BUFFER_SIZE);
		if (c > -1)
			*(buffer + c) = 0;
		if (c == -1 || !update(p_ret, *p_tail))
			return (free(buffer), 0);
		if (!(**p_ret))
			return (free(*p_ret), *p_ret = NULL, \
			free(*p_tail), *p_tail = NULL, 1);
		if (is_end(*p_ret))
			break ;
	}
	return (1);
}

int	update(char **ret, char tail[])
{
	char	*new_ret;
	int		ret_size;
	int		append_size;

	ret_size = ft_strlen_x(*ret, 0);
	append_size = ft_strlen_x(tail, 1);
	new_ret = malloc(sizeof(char) * ret_size + append_size + 1);
	if (!(new_ret))
		return (0);
	ft_strlcpy_gnl(new_ret, *ret, ret_size + 1);
	ft_strlcat_gnl(new_ret, tail, ret_size + append_size + 1);
	free(*ret);
	*ret = new_ret;
	ft_strlcpy_gnl(tail, &tail[append_size], \
	ft_strlen_x(&tail[append_size], 0) + 1);
	return (1);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*result;
// 	int		i;	

// 	// (void)argc;
// 	// (void)argv;
// 	if (argc != 3)
// 	{
// 		printf("Error: \tWrong number of arguments\n");
// 		printf("\t-> First argument must be name of file.\n");
// 		printf("\t-> Second argument must be the number of iterations.\n");
// 		return (0);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	i = atoi(argv[2]);
// 	// i = 10;
// 	while (i--)
// 	{
// 		result = get_next_line(fd);
// 		printf("<%s>", result);
// 		if (result)
// 			free(result);
// 	}
// 	return (0);
// }
