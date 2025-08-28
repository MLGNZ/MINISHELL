/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:15:46 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/27 16:49:48 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_ms *ms)
{
	t_list *temp;
	int cat;
	
	cat = 0;
	while (args && *args)
	{
		temp = exists_in_vars(*args, ms->lst_env, &cat);
		if (temp)
			 ft_lst_remove(temp, &ms->lst_env, 1);
		args++;
	}
	return (1);
}