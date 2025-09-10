/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:36:14 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/09 18:47:03 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**raw_pipeline(char **tb, int len)
{
	char	**ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (0);
	while (++i < len)
	{
		ret[i] = ft_strdup(tb[i]);
		if (!ret[i])
			return (freesplit(ret), NULL);
	}
	ret[i] = NULL;
	return (ret);
}

void	update_r_l(t_pl *pl)
{
	int	i;

	free(pl->raw_pipeline[0]);
	i = 1;
	while (pl->raw_pipeline[i + 1])
	{
		pl->raw_pipeline[i - 1] = pl->raw_pipeline[i];
		i++;
	}
	free(pl->raw_pipeline[i]);
	pl->raw_pipeline[i] = NULL;
	pl->raw_pipeline[i - 1] = pl->raw_pipeline[i];
}

int	malloc_shit(char ***tab, int size)
{
	*tab = malloc(sizeof(char *) * (size + 1));
	if (!*tab)
		return (0);
	**tab = NULL;
	return (1);
}
