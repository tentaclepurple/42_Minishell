/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:15 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/11 13:16:54 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include"../libft/libft.h"
# include<unistd.h>
# include<stdio.h>

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

void	ft_free_split(char **str);

int	    ft_node_quant(char **str);
char	**ft_parse_loop(t_px *node, char **str);
t_px	*ft_parse(char **str);

#endif