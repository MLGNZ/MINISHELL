/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:46:15 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/15 22:19:55 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	printf("%s\n", ft_strdup(*(++argv)));
// 	return (0);
// }