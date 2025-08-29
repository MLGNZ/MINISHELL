/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:27:07 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 22:59:36 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define EOL 1
# define PIPE 2
# define RIN 3
# define ROUT 4
# define HDOC 5
# define AROUT 6

# define SEMICOLON 7
# define AND 8
# define DBSEMICOLON 9
# define ESP 10
# define OR 11

# define O_PAR 12
# define C_PAR 13

# define CMD_LT 1
# define REDIR 2
# define VAR 3

# define ALONE 0 
# define FIRST 1
# define INTER 2
# define LAST 3

typedef struct s_ms
{
	t_list			*lst_env; // environnement
	t_list			*lst_vars; // variables locales
	char			*readline; //ne pas considerer
	char			**s_readline; //ne pas considerer
	int				s_readline_len;// ne pas considerer
	struct s_line	**lns;
	char			prev_exit_code; //pour $?, updater regulierement
	char			exit_code;	//updater regulierement
	int				fd_in;
	int				fd_out;
}	t_ms;

//Each line is composed of different pipelines connected by pipes if multiples.
//Execution of lines depend on priority order, logical operators (ıı, &&, ;, \n) and exit codes of each lines.
typedef struct s_line
{
	struct s_pipeline	**pls; //l'exec se fera la dessus
	// char **vars;
	t_list				*lst_vars; //Ne pas considerer, regarder uniquement ms->lst_vars
	int					nb_of_pls;
	int					ctrl_op; //operateur precedant la pipeline &&, || ou ;
	int					sub_shell;//vrai si subshell
	// char *raw_line;
	char				**split_line;//ne pas considerer
	int					split_line_length;//ne pas considerer
}	t_line;

//Each line has a pipeline, this is something between two pipes or beginning or end or line.
//Each pipeline has a string as command
//An array of string that are cmd + argos
//stored array of string represents redirections (that are going to be freed soon enough)
//the stored in, out, and err as files.
typedef struct s_pipeline
{
	char	*cmd; //commande
	char	**cmd_args; //les arguments
	int		position; //ALONE, FIRST, LAST ou INTER, position de la pipeline dans l'ensemble local de pipelines
	int		sub_shell; //Vrai quand subshell
	char	**redir; //Attention, des fds de gauche peuvent etre invalides (entre 1.048.575 et 2.147.483.647 pour bash
	char	**var; //temp for expansion, ne pas considerer
	t_list	*lst_var;//liste des variables locales assignees par la pipeline, ne pas considerer, regarder uniquement ms->lst_vars
	char	**raw_pipeline;//Ne aps considerer
	int		total_of_pipeline;//Nombre total de pipelines dans cet ensemble
	int		nb_of_this_pipeline;//et son indice (regarder simplement "position")
	/*Le pipe precedent et actuel*/
	//rajouter le necessaire pour exec
	int		pid;
	int		previous_pipe[2];
	int		current_pipe[2];
}	t_pl;

//minishell
int		go_to_subshell(t_ms *ms, char **s_readline);
int		minishell(t_ms *ms, char **s_readline);
int		dive_into_lines(t_ms *ms, t_line **lns);

//parsing
int		clean_all_pipelines(t_ms *ms, t_line *ln);
t_line	**split_and_init_lines(t_ms *ms, char **rline);
int		make_pipeline(char **tb, t_pl **pl_add, int len, int n_o_pls);
int		split_and_init_pipelines(t_ms *ms, t_line **lns, int i);
int		pipeline_len(char **tb);

//exec
int		exec_line(t_ms *ms, t_line *line);

//readline
int		get_valid_line(t_ms *ms, int i);
int		is_there_a_parse_error_near(char **tb);

//aliases
int		alias_in_redir(t_ms *ms, char **s);
int		alias_expansion(t_ms *ms, char **s);
int		clean_expand_in_array(char **tab, char ***tab_addr, t_ms *ms, int type);
int		manage_aliases(t_ms *ms, char **tab, int type);
int		word_length(char *s0, char *s);
int		update_tab(char ***tab_address, char **tab, int i);
char	which_word(char *s, char *s0);
char	*expanded_string(const char *s0, char *s, char *exp, int *len);
char	*get_expansion(const char *s0, t_list *env, t_list *var, t_ms *ms);
int		is_ambiguous(char *exp);
int		replace_token(char **string_address, char *expanded_string);
void	remove_parenthesis_of_line_subshell(t_line *line);
int		pipeline_len(char **tb);
int		is_subshell(char **tab);

//erase
int		panic(t_ms *ms, int err_code);
void	erase_pipelines(t_pl ***pl_address);
void	erase_lines(t_line ***lns_address);

//utils split and join
char	**join_split(char ***ret_addr, char **splt1, char **splt2, int f);
char	**update_split(char ***ret_addr, char **splt1, char **splt2);
int		dup_split(char **split, char ***split_address, int should_free);
int		update_split_just_replace(char **splt1, char **splt2);
char	*ft_strn2join(char const *s1, char const *s2, int n);
char	*ft_strn1join(char *s1, char const *s2, int n);
char	*ft_strjoin_free1(char *s1, char const *s2);
char	*ft_strjoin_free2(char *s1, char *s2);
char	*ft_strjoin_free12(char *s1, char *s2);

//splitop
char	**ft_split_op(char *s, int *len);

//utils
void	printsplit(char **split);
int		how_many_backslashes(char *s0, char *s);
int		is_int(char *s);
int		cw(char *s0, int *len);
char	*ft_getenv(char *key, t_ms *ms);

int		which_op(char *str);
char	is_meta(char *c_address, char meta, char *s0);
char	meta_char(char *rline, char *rline0);
int		find_file(char *cmd, char **file_address, char *path);
int		find_cmd(char**tab, t_ms *ms);
void	offset_array(char ***tab_p);
int		is_build_in(char *str);
int		how_many_backslashes(char *s0, char *s);

//Build in
int		ft_export(char **args, t_ms *ms);
int		ft_unset(char **args, t_ms *ms);
char	*get_var(int pos, t_ms *ms);
void	cd(char **path, t_ms **env);
void	env(t_ms *ms);
int		echo(char **tab);
int		my_get_env(char *var, t_list *env);
void	pwd(t_ms *ms);

void	lst_print(t_list *lst);
int		tab_to_lst(char **tab, t_list **p_lst);
void	ft_lst_remove(t_list *to_rem, t_list **p_list, int free_content);

t_list	*exists_in_vars(char *content, t_list *vars, int *cat);
int		size_of_key(char *content);
int		update_lst(t_list **p_lst_a, t_list **p_lst_b);

//EXEC
int		redirect_fds(t_pl *pipeline);
int		exec_cmd(t_pl **pls, t_ms *ms);
int		red_in(t_pl *pipeline);
int		red_out(t_pl *pl);
#endif
