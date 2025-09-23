/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:22 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/23 16:54:25 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

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

void	sig_handler(int sig)
{
	g_sig = sig + 128;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler_no(int sig)
{
	g_sig = sig + 128;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sig_handler_hd(int sig)
{
	g_sig = sig + 128;
	close(0);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	((void)argc, (void)argv, ft_bzero(&ms, sizeof(t_ms)));
	if (!tab_to_lst(envp, &ms.lst_env))
		return (ft_putstr_fd("Malloc error\n", 2), 1);
	ms.fd_in = dup(0);
	ms.fd_out = dup(1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	while (1)
	{
		if (g_sig)
		{
			ms.exit_code = g_sig;
			g_sig = 0;
		}
		if (!get_valid_line(&ms, -1))
			break ;
		if (ms.s_readline)
		{
			if (**(ms.s_readline) == '-')
				break ;
			ms.prev_exit_code = minishell(&ms, ms.s_readline);
		}
	}
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
