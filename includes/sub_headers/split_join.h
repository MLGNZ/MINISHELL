#ifndef SPLIT_JOIN_H
# define SPLIT_JOIN_H

#include "../minishell.h"

//join_free
char	*ft_strjoin_free1(char *s1, char const *s2);
char	*ft_strjoin_free2(char *s1, char *s2);
char	*ft_strjoin_free12(char *s1, char *s2);

//strnxjoin
char	*ft_strn2join(char const *s1, char const *s2, int n);
char	*ft_strn1join(char *s1, char const *s2, int n);

//joinsplit
char	**join_split(char ***ret_addr, char **splt1, char **splt2, int f);

//split utils
char	*make_word(char *s0, int len);
int		word_length(char *s0, char *s);
int		dup_split(char **split, char ***split_address, int should_free);
int		split_len(char **splt);
void	printsplit(char **split);

//reexpand
char	**ft_split_reexpand(char *s0, int *len);

//update split
int		update_split_just_replace(char **splt1, char **splt2);
char	**update_split(char ***ret_addr, char **splt1, char **splt2);

//splitop
char	**ft_split_op(char *s, int *len);

#endif