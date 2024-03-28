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
# include <string.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>

/*--macro--*/
# define PATH_MAX 4096
# define BUFFER_SZ 4096

/*--struct--*/

typedef struct s_env
{
	struct s_env		*next;
	struct s_env		*previous;
	char				*name;
	char				*value;
}				t_env;

typedef struct s_base
{
	char	***tableau;
	char	*input;
	char	*user;
	char	*cur_pwd;
	char	**env_old;
	char	*output_file;
	char	*command;

	int		terminal_in;
	int		terminal_out;
	int		fd_out;
	int		fd_in;
	// int		ft_custom_exit;
	char	*env_path;
	int		flag_redir;
	int		loop;

	int		pipe;			// not currently used, for pipe implementation
	int		**fd;			// not currently used, for pipe implementation
	int		return_value;
	int		return_value_flag;
	t_env	*env;
}				t_base;

void	change_pwd(t_base *base);
/*--function--*/

	/*-builtin-*/
	/*cd*/
void	ft_free_tab(char **str);
void	modif_path(t_base *base);
void	modif_pwd(t_base *base, char *s);
void	own_cd(char *str, t_base *base); //, t_base *base);
	/*pwd*/
int		get_pwd(t_base *base);

	/*-builtin-*/
	/*-exit-*/
void	exit_prog(int i, void *ptr, t_base *base);
void	free_chain(t_env **chain, t_base *base);
void	ft_exit(t_base *base, int i);

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
void	print_chain(t_env *chain, t_base *base);
char	*get_var_env(t_env *chain, char *name);

		/*listchained2*/
void	add_link(t_env **chain, char *env);
void	add_more_link(t_env **chain, char *env);
void	initial_chain(t_env **chain, char **env);
void	print_list_env(t_env *env_struct, t_base *base);

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
int		ft_find_redirection(char *s);

int		ft_redir(t_base *base, char *fp, char **av, char **tab);
	/*-check-*/
		/*c_quote*/
int		chk_quote(char *s);

		/*c_pipes*/
int		chk_pipe_start(char *s);
int		chk_pipe_end(char *s);

	/*-user-*/
void	init_user(t_base *base);

t_env	*get_link(t_env *chain, char *env);
// void	own_cd(char *str, t_base *base);
int		ft_put_string(t_env *chain, char *name, char *s);

int		countwords(char const *str, int count, int inword, int insidequotes);
void	parser(t_base *base);

int		double_quote(const char *s, int i);
int		ft_special_lword(char *s, int i);
int		ft_strlen_wo_quote(char *s);
char	**ft_special_split(char *s);
char	*ft_strstrip(char *s);
void	own_echo(t_base *base, int k);

int		ft_exec_prog(char **av, t_base *base);
int		ft_export(t_base *base);

int		ft_tablen(char **tab);
int		ft_is_that_char(const char *s, int c);
int		there_is_equal(char *s);
int		find_that_char(char *s, char c);
int		link_already_exist(t_env *chain, char *env);
int		ft_super_countwords(char const *str);
int		check_if_storable(char *s);
char	**ft_super_split(char const *s);
char	*ft_strndup(char *s, int n);
void	ft_unset(t_base *base);
void	remove_old_env(t_base *base, char *var_name);
void	sorted(int argc, char **argv, t_base *base);
void	add_more_link(t_env **chain, char *env);
void	update_more_link(t_env *chain, char *env, t_base *base);

int		ft_strcmp_spe(char *string, char *compared, int srt, int end);
int		is_char_or_num(char c);
char	*get_path_tab(char *input, char **env);

int		get_output_file(char **av, char **ret);
int		get_input_file(char **av, char **ret);
int		only_one_type_redir(char **tab);
int		ft_exec(char **av, char **tab, t_base *base);
int		ft_spe_execve(char **av, char **tab, t_base *base);
char	**get_exec_ready(char **av, t_base *base);
char	**get_good_redir(char **tab);
void	set_inpout(char **ret, t_base *base);
void	multi_redir(char **str, t_base *base, int i);

int		only_one_redir(char **s);
int		ft_left_redir(char **av, t_base *base, int i);
int		is_there_redir(char **s);
int		here_doc(char *eof, t_base *base);
char	**get_exec(char **tab);
void	ft_double_redir(char **av, t_base *base, int i);
void	ft_basic_redir(char **av, t_base *base, int i);
void	ft_double_lredir(t_base *base, int i);
void	child_routin(int pipefd[2], char *eof, char *buf);

int		ft_tablen(char **tab);
int		nb_char(char *s);
int		no_command(char **av);
int		only_one_type_redir(char **tab);
char	*get_my_env(char *name, char **env);
char	*build_exec_path(char *path, char *cmd);
char	*get_path_tab(char *input, char **env);
void	free_tab(char **tab);
void	error(int i, t_base *base);
void	fd_change(t_base *base);

char	*check_last_pipe(char *s);
char	***build_tab(char *s);
char	***pre_build_tab(t_base *base, char *s);//, t_base *base);
char	***ft_ultra_split(char *s);
char	***ft_ultra_while(int j, int k, char ***tab, char **tmp);

int		chrcmp(char c, char *s);
int		hm_pipe(char *s);
int		find_pipe(char *s);
int		tablen_pipe(char **tab, int i);
int		hm_ultra_tab(char ***tab);
char	*correct_input_for_parser(char *s);
void	get_command(char ***tableau, int j, t_base *base);
void	ft_print_env(t_base *base, char *name, int srt, int end);
void	get_file_inpout(t_base *base, char **av, int i);
char	*ft_strdup_markless(char *s);
void	own_env(t_base *base, int i);

int		hm_tab(char **tab);
void	get_input_tab(t_base *base, int i);
int		is_there_char(char *s, char c);
void	gest_dollar(t_base *base, int j, int m);
void	gest_dollar_multipipe(t_base *base);
char	*remove_simple_quote(char *s);
void	tab_printf(char **tab);

int		correct_pipe_len(char *av);
int		correct_redirection_len(char *av);
char	*correct_pipe(char *av);
char 	*correct_pipe_for_parser(char *s);
char	*correct_redirection(char *av);
char 	*correct_input_for_parser(char *s);
char	 *init_input(char *s);
int		here_doc(char *eof, t_base *base);
void	execute_pipeline(char ***command, int nb_cmds, t_base *base);
void	gest_pipe_and_redir2(t_base *base, char ***command, int i);
void	get_input_tab_spe(t_base *base, char **command);
void	free_long_tab(char ***tab);

#endif