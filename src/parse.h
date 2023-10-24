/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:15 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/24 11:49:43 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include"../libft/libft.h"
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

typedef enum	e_mini_error
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
    NODE = 14
}               t_mini_error;

typedef enum    s_type
{
    CMD=1,
    BIp,
    BIc,
    PIPE,
    AND,
    OR
}               t_type;

typedef struct  s_info
{
    int     cmd_amount;
    int     **fd;
    char    **envcp;
    char    *homepath;
}               t_info;

typedef struct  s_px
{
    t_type  type;
    char    *path;
    char    **full_cmd;
    int     in_flag;
    int     out_flag;
    char    *infile;
    char    *outfile;
    char    *limit;
    t_info  *info;
}               t_px;

int    ft_check_var(char **str, char **env);
char	**ft_correc_special(char **str, char *spec);
int 	ft_clean_quotes(char **str);

char	*ft_correct_str(char *str);
char	**ft_split_str(char const *s, char c);
void	ft_free_split(char **str);

int	    ft_node_quant(char **str);
//t_px	*ft_parse(char **str, char **env);
t_px	*ft_parse(char **str, t_info *info);

void	ft_handle_client(int sig);
void	ft_2nd_handler(int sig);

void	*ft_error(int err_type, char *param, int err);
//iban.c
char	*ft_getline(int fd);
void	pipex(t_px *px);
char	*get_cmd_or_cmdpath(char **env, char *str);

//terminal.c
int	    check_no_env(char **env);
//void	terminal(char **env);
void	terminal(t_info *info);

//envutils
char	**ft_env_cpy(char **env);
char	**add_var(char **env, char *var);
char	**del_var_aux(int found, char **env, char **envcpy);
char	**del_var(char **env, char *var);
int 	found_in_env(char *var, char **env, char **path);

//bt_cd.c

//char	**ft_cd(char **env, char **cmdargs);
char	**ft_cd(t_px *px);
char	**ft_cd_update_env(char **env, char *path);

//bt_env_pwd_echo.c
void	ft_pwd(void);
void	ft_echo(t_px *px);
void	ft_env(char **env);

//unset.c
char    **ft_unset(t_px *px);

//export.c
int 	find_equal(char *var, int *found);
void	export_declare(char **env);
char	**ft_export_aux_del(char **env, char **cmdargs, int i, int found);
char	**ft_export_aux(char **env, char **cmdargs);
char	**ft_export(char **env, char **cmdargs);

//ft_manag.c
void	ft_execbi_parent(t_px *px);
void	ft_execbi_child(t_px *px);

int	g_stat;

#endif