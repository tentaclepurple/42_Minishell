/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:15 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/20 09:56:56 by jzubizar         ###   ########.fr       */
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
    BI,
    PIPE,
    AND,
    OR
}               t_type;

typedef struct  s_info
{
    int     cmd_amount;
    int     **fd;
    char    **envcp;
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
t_px	*ft_parse(char **str, char **env);

void	ft_handle_client(int sig);
void	ft_2nd_handler(int sig);

void	*ft_error(int err_type, char *param, int err);
//iban.c
char	*ft_getline(int fd);
void	pipex(t_px *px);
char	*get_cmd_or_cmdpath(char **env, char *str);
//terminal.c
int	    check_no_env(char **env);
void	terminal(char **env);

int	g_stat;

#endif
