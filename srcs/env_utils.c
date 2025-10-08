/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:06:21 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 20:14:51 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_get_env(char *var, t_list *env)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		if (curr->content)
			if (!ft_strncmp(var, curr->content, ft_strlen(var)))
				return (i);
		curr = curr->next;
		i++;
	}
	return (-1);
}

char	*get_var(int pos, t_ms *ms)
{
	t_list	*curr;
	int		i;

	if (pos == -1)
		return (getcwd(NULL, 0));
	curr = ms->lst_env;
	i = -1;
	while (++i < pos)
		curr = curr->next;
	return ((char *)curr->content);
}
