/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:50:48 by josu              #+#    #+#             */
/*   Updated: 2023/10/17 11:36:44 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

/* 
	comp -lreadline terminal.c libft.a -L/Users/$USER/.brew/opt/readline/lib -I/Users/$USER/.brew/opt/readline/include && ./a.out
*/
int	main(int argc, char **argv, char **env)
{
	(void)argv;
	char	**envcp;
  
	if (!check_no_env(env))
		return (printf("Invalid env\n"), -1);
	envcp = ft_dup_2darr(env);
	if (argc != 1)
		return(printf("Invalid arguments\n"), -2);
	envcp = ft_env_cpy(env);
	terminal(envcp);
  ft_free_split(envcp);
	return (0);
}
