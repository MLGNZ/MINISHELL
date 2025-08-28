/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:05:44 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 13:54:44 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_len(char **splt)
{
	int	len;

	len = 0;
	while (splt && *(splt) && ++len)
		splt++;
	return (len);
}

int	dup_split(char **split, char ***split_address, int should_free)
{
	char	**ret;
	int		i;

	i = split_len(split);
	if (!i)
		return (1);
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (0);
	i = 0;
	while (split && *split)
	{
		ret[i] = ft_strdup(*split);
		if (!ret[i++])
			return (freesplit(ret), 0);
		split++;
	}
	ret[i] = NULL;
	if (should_free)
		freesplit(split);
	*split_address = ret;
	return (1);
}
