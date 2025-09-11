/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:49:52 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/11 16:28:34 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ne pas effacer, si pas change, ajouter waitpid dans le gt subshell in line
int	go_to_subshell(t_ms *ms, char **s_readline)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		minishell(ms, s_readline);
		close(ms->fd_in);
		exit(ms->exit_code);
	}
	if (pid < 0)
		return (0);
	return (pid);
}
