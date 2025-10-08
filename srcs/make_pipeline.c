/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:15:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 18:51:57 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pipeline(char **tb, t_pl **pl_address, int len, int n_o_pls)
{
	t_pl	*pl;

	pl = malloc(sizeof(t_pl));
	if (!pl)
		return (0);
	ft_bzero(pl, sizeof(t_pl));
	*pl_address = pl;
	pl->raw_pipeline = raw_pipeline(tb, len);
	if (!pl->raw_pipeline)
		return (0);
	if (pl->raw_pipeline[0][0] == '(')
	{
		pl->sub_shell = 1;
		update_r_l(pl);
		return (1);
	}
	else
	{
		if (!make_arrays_pl(&pl, tb))
			return (0);
		if (!reassign(pl, tb, n_o_pls, -1))
			return (0);
	}
	return (1);
}
