/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:06:32 by vamologl          #+#    #+#             */
/*   Updated: 2024/01/23 11:06:33 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--include--*/
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

/*--macro--*/
#define PATH_MAX 4096

/*--struct--*/


typedef struct s_env
{
	struct s_env		*next;
	struct s_env		*previous;
	char			*name;
	char			*value;
}				t_env;

typedef struct s_base
{
	char	**tableau;
	char	*input;
	char	*user;
	char	*cur_pwd;
	char 	**env_old;

	int		pipe;			// not currently used, for pipe implementation
	int 	**fd;			// not currently used, for pipe implementation
	int		return_value;	// not currently used, for $? implementation

	t_env		*env;
}				t_base;


void change_pwd(t_base *base); 
/*--function--*/

	/*-builtin-*/
	/*cd*/
void	ft_free_tab(char **str);
void	modif_path(t_base *base);
void	modif_pwd(t_base *base, char *s);
void	own_cd(char *str); //, t_base *base);
	/*pwd*/
int	get_pwd(t_base *base);

	/*-builtin-*/
	/*-exit-*/
void	exit_prog(int i, void *ptr);
void	free_chain(t_env **chain);
void	ft_exit(t_env **chain);

	/*-utils-*/
int		cmp_len(char *s1, char *s2);
int		find_equal(char *s);
char	*ft_dup_name(char *env);
char	*ft_dup_value(char *env);
int		is_empty(char *s);

	/*-utils2-*/
void	*ft_find_quote(char *s);
char	**ft_get_text(char *s);
int		ft_strcmp(char *s1, char *s2);

	/*-list-*/
		/*listchained*/
int		ft_strcmp(char *s1, char *s2);
char	*ft_shlvl_var(char *s2);
t_env	*find_last(t_env *head);
void    print_chain(t_env *chain);
char    *get_var_env(t_env *chain, char *name);

		/*listchained2*/
void    add_link(t_env **chain, char *env);
void    add_more_link(t_env **chain, char *env);
void    initial_chain(t_env **chain, char **env);
void	print_list_env(t_env *env_struct);

	/*-list-*/
void	initial_list(t_env **env, char **variable_env);

	/*-parser-*/
		/*separ*/
char	**ft_separ(char *s, char c);

		/*parser_error*/
void	message_error(char *s, int flag);
int		chk_directory2(char *str, int i);
int		chk_directory(t_base *base);

		/*parser_utils*/
int		skip_whitespace(char *string, int i);
int		just_whitespace(char *s, int i);
int		ft_strnlen(char *s, int i);
char	*spaceless_strdup(t_base *base);
int		only_dots(char *s, int i);
int		many_dots(char *s, int i);
int		ft_find_redirection(char const *s, int i);

int		ft_redir(t_base *base);
	/*-check-*/
		/*c_quote*/
int		chk_quote(char *s);

		/*c_pipes*/
int		chk_pipe_start(char *s);
int		chk_pipe_end(char *s);

	/*-user-*/
void	init_user(t_base *base);

// void	own_cd(char *str, t_base *base);
int		ft_put_string(t_env *chain, char *name, char *s);

void	parser(t_base *base);
int		countwords(char const *str, int count, int inword, int insidequotes);
void	get_input_tab(t_base *base);

int		double_quote(const char *s, int i);
int		ft_special_lword(char const *s, int i);
char	**ft_special_split(char const *s);
int		ft_strlen_wo_quote(char *s);
char	*ft_strstrip(char *s);

void	own_echo(t_base *base);


int 	ft_exec_prog(char **av, t_base *base);
int		ft_export(t_base *base);

char	*ft_strndup(const char *s, int n);
void 	ft_unset(t_base *base);
int		ft_tablen(char **tab);
int		ft_is_that_char(const char *s, int c);
void	remove_old_env(t_base *base, char *var_name);
int		there_is_equal(char *s);
int 	find_that_char(char *s, char c);
void	sorted(int argc, char **argv);
void 	add_more_link(t_env **chain, char *env);
void 	update_more_link(t_env *chain, char *env);
t_env	*get_link(t_env *chain, char *env);
int		link_already_exist(t_env *chain, char *env);
char 	**ft_super_split(char const *s);
int 	ft_super_countwords(char const *str);
int 	check_if_storable(char *s);

#endif