/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:27:07 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 15:14:50 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "sub_headers/ext_lib.h"
# include "sub_headers/define.h"
# include "libft.h"
# include "sub_headers/structures.h"
# include "sub_headers/var_expansion.h"
# include "sub_headers/wildcards.h"
# include "sub_headers/built_in.h"
# include "sub_headers/mini_signal.h"
# include "sub_headers/split_join.h"
# include "sub_headers/get_readline.h"
# include "sub_headers/parse_error.h"
# include "sub_headers/tab_and_lst.h"

extern volatile sig_atomic_t	g_sig;

//minishell
int		minishell(t_ms *ms, char **s_readline);

//nothing (do not remove)
void	nothing(void *whatever);

//make arrays of pipelines
int		make_arrays_pl(t_pl **pl, char **tb);

//UPDATE TAB
int		update_tab(char ***tab_address, char **tab, int i);

//env utils
char	*get_var(int pos, t_ms *ms);
int		my_get_env(char *var, t_list *env);
char	*ft_getenv(char *key, t_ms *ms);;
int		add_new_elem(t_list **p_lst, char *content, char *var);
int		fill_new_env(t_list **p_lst);

//erase
int		panic(t_ms *ms, int err_code);
void	erase_pipelines(t_pl ***pl_address);
void	erase_lines(t_line ***lns_address);

//parsing
t_line	**split_and_init_lines(t_ms *ms, char **rline);
int		split_and_init_pipelines(t_ms *ms, t_line **lns, int i);
int		make_pipeline(char **tb, t_pl **pl_add, int len, int n_o_pls);
int		clean_all_pipelines(t_ms *ms, t_line *ln);
int		clean_expand_in_array(char **tab0, char ***tab_add, t_ms *ms, int type);

//Utils parsing.c
int		find_cmd(char**tab, t_ms *ms);
int		is_build_in(char *str);
void	remove_quotes(const char *s0, char *s);
void	remove_backslashes(const char *s0, char *s);
char	is_meta(char *c_address, char meta, char *s0);
char	meta_char(char *rline, char *rline0);
int		is_int(char *s);
int		how_many_backslashes(char *s0, char *s);
int		which_op(char *str);
int		is_var_ass(char *str);
int		cw(char *s0, int *len);
char	which_word(char *s, char *s0);

//reassign.c
int		reassign(t_pl *pl, char **tab, int n_o_pls, int i);

//find_file.c
int		find_file(char *cmd, char **file_address, char *path, int i);

//updatelst.c
int		update_lst(t_list **p_lst_a, t_list **p_lst_b);
t_list	*exists_in_vars(char *content, t_list *vars, int *cat);
char	*cat_vars(char *var1, char *var2, int free2);
int		size_of_key(char *content);

//go to subshell.c
int		go_to_subshell(t_ms *ms, char **s_readline);
void	protect_subshell(t_ms *ms, t_pl **pls, int *i);
int		handle_subshell(t_pl **pls, int *i, t_ms *ms);
int		is_subshell(char **tab);

//lstutils.c
void	lst_print(t_list *lst);
void	ft_lst_remove(t_list *to_rem, t_list **p_list, int free_content);

//RANGER MIEUX TOUT CE QUI EST EN DESSOUS

//exec
int		dive_into_lines(t_ms *ms, t_line **lns);
int		exec_line(t_ms *ms, t_line *line);
int		exec_cmd(t_pl **pls, t_ms *ms);

//red in
int		red_in(t_pl *pipeline, t_ms *ms);
int		look_hd(t_pl *pl, int last[3], t_ms *ms);

//ambiguous
int		is_ambiguous(char *exp);
void	ambiguous_message(char *s);

//bordel

void	handle_pipe(t_pl *pl);
int		handle_built_in(t_pl **pls, int *i, t_ms *ms);
int		redirect_out_fd(t_pl **pl, char *redir, t_pl *temp, int i);
int		pipe_needed(t_pl *pl);
void	reset_out_fds(t_pl *pl);
int		handle_built_in(t_pl **pls, int *i, t_ms *ms);
int		handle_fds(t_pl **pls, int i, t_ms *ms);
void	close_fds(int fd1, int fd2, int fd3, int fd4);
void	my_dup2(int fd1, int fd2, int fd3, int fd4);
int		red_out(t_pl *pl, t_ms *ms);
int		handle_redirs(t_ms *ms, t_pl **pls, int *i);
void	get_status(int status, t_ms *ms);
void	incr_shlvl(t_list **env, t_ms *ms);

#endif
