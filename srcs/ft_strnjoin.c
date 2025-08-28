/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:05:57 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 14:20:55 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strn2join(char const *s1, char const *s2, int n)
{
	char	*ret;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len2 > n)
		len2 = n;
	ret = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, len1 + 1);
	ft_strlcat(ret, s2, len1 + len2 + 1);
	return (ret);
}

char	*ft_strn1join(char *s1, char const *s2, int n)
{
	char	*ret;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > n)
		len1 = n;
	ret = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, len1 + 1);
	ft_strlcat(ret, s2, len1 + len2 + 1);
	return (ret);
}
