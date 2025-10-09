/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:15:05 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 15:16:59 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPANSION_H
# define VAR_EXPANSION_H

# include "../minishell.h"

//VAR EXPANSION
int		manage_aliases(t_ms *ms, char **tab, int type);
int		alias_expansion(t_ms *ms, char **s);
int		alias_in_redir(t_ms *ms, char **s);
//utils
char	*expanded_string(const char *s0, char *s, char *exp, int *len);
char	*get_expansion(const char *s0, t_list *env, t_list *var, t_ms *ms);
int		replace_token(char **string_address, char *expanded_string);

#endif