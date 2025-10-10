/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:15:02 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/10 12:27:49 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include "../minishell.h"

//WILDCARDS
int		manage_wildcards(t_ms *ms, char **tab, int type, t_list **lst_wc);
int		wildcards_expansion_in_cmd(char **s, t_list **lst);
int		wildcards_in_redir(char **s);
//pattern and match
char	**get_wild_pattern(char **s, int *first_n_last, int wc, int *check);
int		match_wild_pattern(char *d_name, char **wild_pattern, int fnl);
//utils
int		ft_strcasecmp(const char *s1, const char *s2);
void	sort_wild(t_list **lst);
void	put_back_slash_at_the_end_if_necessary(char **str_ptr, int is_dir);
int		handle_no_match(t_list **mf, char **s, int is_dir);
char	*wild_join(char *src, char *d_name);

#endif