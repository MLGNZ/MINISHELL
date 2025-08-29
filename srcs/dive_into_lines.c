/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dive_into_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:11:44 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 22:34:00 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dive_into_lines(t_ms *ms, t_line **lns)
{
	int	i;

	i = -1;
	while (lns && lns[++i])
	{
		printf("++++++++++++++++++++++++++++++++\n\nLine n.%i:\n", i + 1);
		printf("control operator of line: %i\n", lns[i]->ctrl_op);
		if (!split_and_init_pipelines(ms, lns, i))
			return (0);
		exec_line(ms, lns[i]);
		// printf("\n");
	}
	erase_lines(&(ms->lns));
	return (1);
}

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
	(void)lns;
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
		// free(pl->cmd);
		freesplit(pl->cmd_args);
		freesplit(pl->redir);
		freesplit(pl->var);
		ft_lstclear(&pl->lst_var, free);
		free(pl);
	}
	free(pls);
	*pls_address = NULL;
}
