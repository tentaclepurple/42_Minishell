#include"../src/parse.h"


/*int	main()
{
	char **cmdargs = {"ls", "ma*l*txt", "*.c"	};

	//if there is * in the arguments loop (leave \*, careful with just *)

		//readdir loop. count (ignore "." and "..") 
		//malloc char ** new_cmdargs. put cmd in [0] put "\0"

		//search & keep head_pattern, core_paterns and tail_paterns

		//readdir loop
		
			//if it´s not already copied compare paterns and copy to new_cmdargs  

}*/

int	main()
{
	char *pattern = "*ni*";
	char *target = "minishell.c";

	int	i = 0;
	int	j = 0;
	while (target[i])
	{
		if (pattern[j] == target[i] && pattern[j] 
	}


}

