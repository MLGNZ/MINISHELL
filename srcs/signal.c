/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:10:01 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/08 16:59:29 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	sig_handler_close(int sig)
{
	close(0);
	g_sig = sig + 128;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sig_handler_quit(int sig)
{
	printf("Quit (core dumped)\n");
	g_sig = sig + 128;
	rl_replace_line("", 0);
	rl_on_new_line();
}
