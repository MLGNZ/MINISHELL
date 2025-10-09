/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:22 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:16:09 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	((void)argc, (void)argv, ft_bzero(&ms, sizeof(t_ms)));
	if (!tab_to_lst(envp, &ms.lst_env))
		return (ft_putstr_fd("Malloc error\n", 2), 1);
	if (!ms.lst_env)
		fill_new_env(&ms.lst_env);
	else
		incr_shlvl(&ms.lst_env, &ms);
	ms.fd_in = dup(0);
	ms.fd_out = dup(1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	while (1)
	{
		if (!get_valid_line_inter(&ms, -1))
			break ;
		if (ms.s_readline)
			ms.prev_exit_code = minishell(&ms, ms.s_readline);
	}
	close(ms.fd_in);
	close(ms.fd_out);
	panic(&ms, ms.exit_code);
	return (0);
}

int	minishell(t_ms *ms, char **s_readline)
{
	ms->s_readline = s_readline;
	ms->lns = split_and_init_lines(ms, ms->s_readline);
	dive_into_lines(ms, ms->lns);
	return (ms->exit_code);
}
