/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_and_lst.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:15:09 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 15:15:10 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAB_AND_LST_H
# define TAB_AND_LST_H

# include "../minishell.h"

char	**lst_to_tab(t_list *env);
int		tab_to_lst(char **tab, t_list **p_lst);

#endif 