/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:49:52 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/08 11:48:22 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_subshell(t_ms *ms, char **s_readline)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (!pid)
		exit(minishell(ms, s_readline));
	if (pid < 0)
		return (0);
	if (pid)
		waitpid(pid, &status, 0);
	ms->prev_exit_code = status;
	return (1);
}
