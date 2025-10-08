/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 19:27:02 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/26 16:33:26 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_wildcards(t_ms *ms, char **tab, int type, t_list **lst)
{
	char	**wcs;

	if (type == CMD_LT && !wildcards_expansion_in_cmd(tab, lst))
		return (panic(ms, 52), 0);
	if (type == REDIR && !wildcards_in_redir(ms, tab))
		return (0);
	return (1);
}
