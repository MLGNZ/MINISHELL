/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:25:11 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/04 17:35:07 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	panic(t_ms *ms, int err_code)
{
	if (err_code == 52)
		ft_putstr_fd("minishell: malloc failure\n", 2);
	if (ms)
	{
		// freesplit(ms->envp);
		// freesplit(ms->vars);
		freesplit(ms->s_readline);
		ft_lstclear(&ms->lst_env, free);
		ft_lstclear(&ms->lst_vars, free);
		if (ms->lns)
			erase_lines(&(ms->lns));
	}
	if (err_code >= 0)
		exit(err_code);
	exit(ms->exit_code);
	return (1);
}
