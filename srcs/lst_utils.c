/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:04:41 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:06:00 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_remove(t_list *to_rem, t_list **p_list, int free_content);
void	lst_print(t_list *lst);

void	ft_lst_remove(t_list *to_rem, t_list **p_list, int free_content)
{
	t_list	*list;

	if (!to_rem || !*p_list)
		return ;
	list = *p_list;
	if (list == to_rem)
	{
		*p_list = list->next;
		if (free_content)
			free(to_rem->content);
		free(to_rem);
		return ;
	}
	while (list && list->next)
	{
		if (list->next == to_rem)
		{
			list->next = to_rem->next;
			if (free_content)
				free(to_rem->content);
			free(to_rem);
		}
		list = list->next;
	}
}

void	lst_print(t_list *lst)
{	
	while (lst)
	{
		puts(lst->content);
		lst = lst->next;
	}
}
