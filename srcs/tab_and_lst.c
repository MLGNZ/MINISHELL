/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_and_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:24:23 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 12:25:17 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	tab_to_lst(char **tab, t_list **p_lst)
{
	char	*content;
	t_list	*temp_list;

	while (tab && *tab)
	{
		content = ft_strdup(*tab);
		if (!content)
			return (ft_lstclear(p_lst, free), 0);
		temp_list = ft_lstnew(content);
		if (!temp_list)
			return (ft_lstclear(p_lst, free), free(content), 0);
		ft_lstadd_back(p_lst, temp_list);
		tab++;
	}
	return (1);
}
