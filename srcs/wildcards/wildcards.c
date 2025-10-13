/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/10 19:36:34 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_wildcards(t_ms *ms, char **tab, int type, t_list **lst)
{
	if (type == CMD_LT && !wildcards_expansion_in_cmd(tab, lst))
		return (panic(ms, 52), 0);
	if (type == REDIR && !wildcards_in_redir(tab))
		return (0);
	return (1);
}
