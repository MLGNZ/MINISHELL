/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:37:28 by mlagniez          #+#    #+#             */
/*   Updated: 2025/06/24 15:56:34 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# if BUFFER_SIZE > 2147483646
#  undef BUFFER_SIZE
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd, int *check);
int		read_through(int fd, char **p_ret, char **p_tail);
int		update(char **ret, char tail[]);
int		is_end(char *check);
char	*freetail(char *tail);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t siz);
size_t	ft_strlen_x(const char *s, int nb);
size_t	ft_strlcat_gnl(char *dst, const char src[], size_t siz);

#endif
