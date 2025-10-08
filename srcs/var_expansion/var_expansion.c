/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:33:04 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 19:45:41 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_aliases(t_ms *ms, char **tab, int type)
{
	if (type == CMD_LT)
		alias_expansion(ms, tab);
	if (type == REDIR && !alias_in_redir(ms, tab))
		return (0);
	if (type == VAR)
		alias_expansion(ms, tab);
	return (1);
}
