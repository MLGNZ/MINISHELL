/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:07:43 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 14:18:42 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_len(char **splt)
{
	int	len;

	len = 0;
	while (splt && *(splt) && ++len)
		splt++;
	return (len);
}

char	**join_split(char ***ret_addr, char **splt1, char **splt2, int freee)
{
	int		i;
	char	**ret;
	char	**ret0;

	i = 0;
	i += split_len(splt1);
	i += split_len(splt2);
	ret0 = malloc(sizeof(char *) * (i + 1));
	if (!ret0)
		return (NULL);
	ret = ret0;
	i = -1;
	while (splt1 && splt1[++i])
		*(ret++) = splt1[i];
	i = -1;
	while (splt2 && splt2[++i])
		*(ret++) = splt2[i];
	*ret = NULL;
	if (*ret_addr == splt1)
		free(splt1);
	*ret_addr = ret0;
	if (freee)
		return (free(splt1), free(splt2), splt1 = NULL, splt2 = NULL, ret0);
	return (ret0);
}
