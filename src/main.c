/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:50:48 by josu              #+#    #+#             */
/*   Updated: 2023/10/14 20:25:39 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

/* 
	comp -lreadline terminal.c libft.a -L/Users/$USER/.brew/opt/readline/lib -I/Users/$USER/.brew/opt/readline/include && ./a.out
*/
int	main(int argc, char **argv, char **env)
{
	(void)argv;
	char *var = getenv("USER");

	printf("%s\n", var);
	if (!check_no_env(env))
		return (printf("Invalid env\n"), -1);
	if (argc != 1)
		return(printf("Invalid arguments\n"), -2);
	terminal(env);
	return (37);
}