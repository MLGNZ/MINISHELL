/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:27:07 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 21:20:20 by mlagniez         ###   ########.fr       */
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

extern volatile sig_atomic_t	g_sig;

//minishell
int		minishell(t_ms *ms, char **s_readline);

//nothing (do not remove)
void	nothing(void *whatever);

//make arrays of pipelines
int	make_arrays_pl(t_pl **pl, char **tb);

//UPDATE TAB
int		update_tab(char ***tab_address, char **tab, int i);

//env utils
char	*get_var(int pos, t_ms *ms);
int		my_get_env(char *var, t_list *env);

//erase
int		panic(t_ms *ms, int err_code);
void	erase_pipelines(t_pl ***pl_address);
void	erase_lines(t_line ***lns_address);

//readline
int		get_valid_line(t_ms *ms, int i);
int		is_there_a_parse_error_near(char **tb);


//RANGER MIEUX TOUT CE QUI EST EN DESSOUS

//parsing
int		clean_all_pipelines(t_ms *ms, t_line *ln);
int		parenthesis(char **tb);
t_line	**split_and_init_lines(t_ms *ms, char **rline);
int		make_pipeline(char **tb, t_pl **pl_add, int len, int n_o_pls);
int		split_and_init_pipelines(t_ms *ms, t_line **lns, int i);
int		update_vars_from_export_args(t_list **p_lst_args, t_list **p_lst_vars);
int		pipeline_len(char **tb);
char	**raw_pipeline(char **tb, int len);
void	update_r_l(t_pl *pl);
int		parse_error(int operator, char *token, int is_unsupported);
int		make_pipeline(char **tb, t_pl **pl_address, int len, int n_o_pls);
int		malloc_shit(char ***tab, int size);
int		is_var_ass(char *str);

//exec
int		exec_line(t_ms *ms, t_line *line);
int		exec_cmd(t_pl **pls, t_ms *ms);

//bordel
int		how_many_backslashes(char *s0, char *s);
int		is_int(char *s);
int		cw(char *s0, int *len);
char	*ft_getenv(char *key, t_ms *ms);
int		which_op(char *str);
char	is_meta(char *c_address, char meta, char *s0);
char	meta_char(char *rline, char *rline0);
int		find_file(char *cmd, char **file_address, char *path, int i);
int		find_cmd(char**tab, t_ms *ms);
int		is_build_in(char *str);
int		how_many_backslashes(char *s0, char *s);
void	lst_print(t_list *lst);
int		tab_to_lst(char **tab, t_list **p_lst);
void	ft_lst_remove(t_list *to_rem, t_list **p_list, int free_content);
t_list	*exists_in_vars(char *content, t_list *vars, int *cat);
char	*cat_vars(char *var1, char *var2, int free2);
int		size_of_key(char *content);
int		update_lst(t_list **p_lst_a, t_list **p_lst_b);
char	**lst_to_tab(t_list *env);
void	handle_pipe(t_pl *pl);
int		handle_built_in(t_pl **pls, int *i, t_ms *ms);
int		red_in(t_pl *pipeline, t_ms *ms);
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



//TBD
void	ambiguous_message(char *s);
int		go_to_subshell(t_ms *ms, char **s_readline);

int		dive_into_lines(t_ms *ms, t_line **lns);

void	incr_shlvl(t_list **env, t_ms *ms);
int		handle_subshell(t_pl **pls, int *i, t_ms *ms);
int		get_valid_line_inter(t_ms *ms, int i);
char	*make_word(char *s0, int len);
char	**ft_split_reexpand(char *s0, int *len);
int		reassign(t_pl *pl, char **tab, int n_o_pls, int i);
void	remove_quotes(const char *s0, char *s);
void	remove_backslashes(const char *s0, char *s);
void	sig_handler_noendl(int sig);
int		alias_expansion(t_ms *ms, char **s);
int		clean_expand_in_array(char **tab, char ***tab_addr, t_ms *ms, int type);
int		word_length(char *s0, char *s);
char	which_word(char *s, char *s0);
int		is_ambiguous(char *exp);
void	remove_parenthesis_of_line_subshell(t_line *line);
int		pipeline_len(char **tb);
int		is_subshell(char **tab);


#endif
