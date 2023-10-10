/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:15 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/10 18:15:01 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include"../libft/libft.h"
# include<unistd.h>
# include<stdio.h>

void    ft_check_var(char **str, char **env);
char	**ft_correc_special(char **str, char *spec);

typedef enum    s_type
{
    CMD,
    PIPE,
    AND,
    OR
}               t_type;

typedef struct  s_node
{
    t_type  type;
    char    *path;
    char    **cmd;
    int     input;
    int     output;
}               t_node;


#endif