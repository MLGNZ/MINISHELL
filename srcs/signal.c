/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:10:01 by tchevall          #+#    #+#             */
/*   Updated: 2025/09/25 16:20:48 by tchevall         ###   ########.fr       */
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

void	sig_handler_hd(int sig)
{
	g_sig = sig + 128;
	close(0);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sig_handler_prompt(int sig)
{
	g_sig = sig + 128;
	close(0);
	rl_replace_line("", 0);
	rl_on_new_line();
}
