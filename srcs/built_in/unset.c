/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:15:46 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/01 15:42:39 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_ms *ms)
{
	t_list	*temp;
	int		cat;

	cat = 0;
	if (!*(++args))
		return (0);
	while (args && *args)
	{
		temp = exists_in_vars(*args, ms->lst_env, &cat);
		if (temp)
			ft_lst_remove(temp, &ms->lst_env, 1);
		args++;
	}
	return (1);
}

char	**lst_to_tab(t_list *env)
{
	t_list	*curr;
	char	**tab;
	int		i;

	curr = env;
	i = 0;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	curr = env;
	i = 0;
	while (curr)
	{
		tab[i++] = curr->content;
		curr = curr->next;
	}
	tab[i] = NULL;
	return (tab);
}
