/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:15 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/14 19:43:04 by josu             ###   ########.fr       */
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

/*# include "../colors.h"
# include "../pipex.h"
# include "../../terminal.h"*/

typedef enum    s_type
{
    CMD,
    PIPE,
    AND,
    OR
}               t_type;

typedef struct  s_info
{
    int     cmd_amount;
    int     **fd;
}               t_info;

typedef struct  s_px
{
    char    *path;
    char    **full_cmd;
    int     in_flag;
    int     out_flag;
    char    *infile;
    char    *outfile;
    char    *limit;
    t_info  *info;
}               t_px;

void    ft_check_var(char **str, char **env);
char	**ft_correc_special(char **str, char *spec);

char	*ft_correct_str(char *str);
char	**ft_split_str(char const *s, char c);
void	ft_free_split(char **str);

int	    ft_node_quant(char **str);
t_px	*ft_parse(char **str, char **env);


//iban.c
char	*ft_getline(int fd);
void	pipex(t_px *px);
char	*get_cmd_or_cmdpath(char **env, char *str);
//terminal.c
int	    check_no_env(char **env);
void	terminal(char **env);

#endif