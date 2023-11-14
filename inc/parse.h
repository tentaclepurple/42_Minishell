/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:15 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/14 17:04:42 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>

/*# include "../colors.h"
# include "../pipex.h"
# include "../../terminal.h"*/

# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define GREENB		"\033[32;1m"
# define YELLOW		"\033[0;33m"
# define BLUE 		"\033[0;34m"
# define BLUEB 		"\033[34;1m"
# define PURPLE		"\033[0;35m"
# define PURPLEB	"\033[35;1m"
# define CYAN		"\033[0;36m"
# define BOLD		"\033[0;1m"
# define X			"\033[0;0m"

typedef enum e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	SYNERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13,
	NODE = 14,
	HOMSET,
	OPWDSET
}	t_mini_error;

typedef enum s_type
{
	NONE=0,
	CMD,
	BIp,
	BIc,
	PIPE,
	AND,
	OR
}	t_type;

typedef struct s_info
{
	int		cmd_amount;
	int		**fd;
	char	**envcp;
	char	*homepath;
}	t_info;

typedef struct s_px
{
	t_type	type;
	char	*path;
	char	**full_cmd;
	int		in_flag;
	int		out_flag;
	char	*infile;
	char	*outfile;
	char	*limit;
	t_info	*info;
}	t_px;

int		ft_check_var(char **str, char **env);
char	**ft_correc_special(char **str, char *spec);
int		ft_clean_quotes(char **str);

//Split
int		ft_str_chlen(char const *s, char c);
int		ft_nbr_wrd(char const *s, char c);
char	*ft_fill_word(char *wrd, char *str, int len);
void	ft_mv_in_quotes(char const *s, unsigned int *i);
char	*ft_correct_str(char *str);
char	**ft_split_str(char const *s, char c);
void	ft_free_split(char **str);
char	**ft_inout_file(t_px *node, char **str);
int		ft_is_cm(char *str, t_px *node);
int		ft_num_args(char **str);
void	ft_handle_client(int sig);
void	ft_2nd_handler(int sig);
size_t	ft_strlen_var(const char *s, int quote);
int		ft_len_var_cond(char *env, char *str, int index, int quote);
char	*ft_expand_concat(char *env, int len, char *res, char ch);
int		ft_check_inout(char **str);

/* 
parse
*/
t_px	*ft_parse(char **str, t_info *info);
int		ft_node_quant(char **str);
void	ft_free_nodes(t_px *nodes);
char	**ft_parse_loop(t_px *node, char **str, char **env);
t_px	*ft_init_nodes(t_info *info);
int		ft_check_nodes(t_px *nodes);
void	ft_stat_signaled(void);
char	**ft_fill_full_cmd(t_px *node, int num_arg, char **str);

/*
ERROR.C
*/
void	*ft_error(int err_type, char *param, int err);
void	*ft_bt_error(int err_type, char *param, int err);

/*
executor.c
*/
void	pipex(t_px *px);
int		pipex_p(t_px *px);
void	ft_output_redirect(t_px *px);
void	ft_input_redirect(t_px *px);
void	ft_fd_pipes(t_px *px, int n);
void	ft_child(t_px *px, int n);
char	*get_cmd_or_cmdpath(char **env, char *str);
char	*ft_getline(int fd);
char	**get_path(char **env);
int		check_slash(char *str);
void	ft_fd_close(t_px *px, int j);
void	ft_alloc_fd(t_px *px);
void	ft_free_fd(t_px *px);
void	write_here_doc_tmp(t_px *px);
void	ft_getline_aux(char c, char **str);
void	pipex_p_aux(t_px *px, int i, pid_t pid);

/*
terminal.c
*/
int		check_no_env(char **env);
void	terminal(t_info *info);
int		check_env_and_vars(char **env);
void	terminal_options(char *input);
void	ft_open_outfiles(t_px *nodes);
int		ft_lines2(char *str, t_info *info, char ***res);
void	ft_open_outfiles(t_px *nodes);

/*
envutils
*/
char	**ft_env_cpy(char **env);
char	**add_var(char **env, char *var);
char	**del_var_aux(int found, char **env, char **envcpy);
char	**del_var(char **env, char *var);
int		found_in_env(char *var, char **env, char **path);
int		ft_is_dir(const char *name);

/*
bt_cd.c
*/
char	**ft_cd(t_px *px);
char	**ft_cd_update_env(char **env, char *path);
void	ft_cd_home(t_px *px, char ***envcpy);
void	ft_cd_oldpwd(t_px *px, char ***envcpy);
void	ft_cd_tilde(t_px *px, char ***envcpy);

/*
bt_env_pwd_echo.c
*/
int		ft_pwd(void);
int		ft_echo(t_px *px);
int		ft_env(char **env);

/*
unset.c
*/
char	**ft_unset(t_px *px);

/*
export.c
*/
int		find_equal(char *var, int *found);
void	export_declare(char **env);
char	**ft_export_aux_del(char **env, char **cmdargs, int i, int found);
char	**ft_export_aux(char **env, char **cmdargs);
char	**ft_export(char **env, char **cmdargs);

/*
ft_manag.c
*/
int		ft_execbi_parent(t_px *px);
void	ft_execbi_child(t_px *px);

/*
bt_exit.c
*/
int		ft_bt_exit(t_px *node);

/* 
wildcard
 */
void	fill_exp_cmdargs(char *pattern, char ***exp_cmdargs);
void	ft_wildcard(char ***cmdargs);
int		ft_matlen(char **mat);
int		count_dir(void);
char	**create_exp_cmdargs(char **cmdargs, int *size);
int		find_wild_match(char *pattern, char *str);
char	**trim_excess(char **exp, int size);

int	g_stat;

#endif