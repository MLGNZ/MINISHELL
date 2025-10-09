/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:08:36 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:21:10 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_lines(t_line ***lns_add);
void	erase_pipelines(t_pl ***pls_address);

void	erase_lines(t_line ***lns_add)
{
	t_line	**lns;

	lns = *lns_add;
	while (lns && *lns)
	{
		ft_lstclear(&(*lns)->lst_vars, free);
		freesplit((*lns)->split_line);
		if ((*lns)->pls)
			erase_pipelines(&(*lns)->pls);
		free((*lns)->pls);
		free(*lns);
		lns++;
	}
	free(*lns_add);
	*lns_add = NULL;
}

void	erase_pipelines(t_pl ***pls_address)
{
	t_pl	**pls;
	t_pl	*pl;
	int		i;

	pls = *pls_address;
	i = -1;
	while (pls[++i])
	{
		pl = pls[i];
		freesplit(pl->raw_pipeline);
		freesplit(pl->cmd_args);
		freesplit(pl->redir);
		freesplit(pl->var);
		ft_lstclear(&pl->lst_var, free);
		free(pl);
	}
	free(pls);
	*pls_address = NULL;
}
