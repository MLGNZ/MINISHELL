/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:22 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 21:04:39 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	((void)argc, (void)argv, ft_bzero(&ms, sizeof(t_ms)));
	if (!tab_to_lst(envp, &ms.lst_env))
		return (ft_putstr_fd("Malloc error\n", 2), 1);
	ms.fd_in = 1;
	ms.fd_out = 0;
	while (1)
	{
		if (!get_valid_line(&ms, -1))
			break ;
		if (ms.s_readline)
		{
			if (**(ms.s_readline) == '-')
				break ;
			ms.prev_exit_code = minishell(&ms, ms.s_readline);
		}
	}
	puts("+++++++++++++=exit++++++++++++++++++++++++++++++++++++++++++++++");
	panic(&ms, -1);
	return (0);
}

int	minishell(t_ms *ms, char **s_readline)
{
	ms->s_readline = s_readline;
	printsplit(ms->s_readline);
	ms->lns = split_and_init_lines(ms, ms->s_readline);
	dive_into_lines(ms, ms->lns);
	return (ms->exit_code);
}
