https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

https://github.com/Swoorup/mysh

https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

https://github.com/madebypixel02/minishell/blob/main/README.md

https://www.youtube.com/watch?v=4jYFqFsu03A&list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW&index=7



En makefile

      -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

Comp

      comp -lreadline terminal.c libft.a -L/Users/$USER/.brew/opt/readline/lib -I/Users/$USER/.brew/opt/readline/include && ./a.out

Readline Library

      https://tiswww.case.edu/php/chet/readline/readline.html

Para compilar readline
   
      -L/Users/$USER/.brew/opt/readline/lib 
      -I/Users/$USER/.brew/opt/readline/include




suprimir leaks readline

      valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell


------

- [ ] Compile

      - USE make -n to see if compilation use -Wall -Wextra -Werror if not use invalid compilation flags
      - minishell Compile without errors if not use flags
      - makefile must not re-link
      
- [ ] Simple Command & global

      - Execute a simple command with an absolute path like /bin/ls or any other command without options
      - How many global variables? why? Give a concrete example of why it feels mandatory or logical.
      - Test an empty command.
      - Test only spaces or tabs.
      - if something crashes use the crash flag.
      - if something is not working use the incomplete work flag.

- [ ] Arguments & history

        - Execute a simple command with an absolute path like /bin/ls or any other command with arguments but without
          quotes and double quotes
        - Repeat multiple times with different commands and arguments
        - if something crashes use the crash flag.
        - if something is not working use the incomplete work flag.

      
- [ ] echo

        - Execute the echo command with or without arguments or -n
        - Repeat multiple times with different arguments
        - if something crashes use the crash flag.
        - if something is not working use the incomplete work flag.


- [ ] exit
    
        - Execute exit command with or without arguments
        - Repeat multiple times with different arguments
        - Don't forget to relaunch the minishell
        - if something crashes use the crash flag.
        - if something is not working use the incomplete work flag
      
- [ ] Return value of a process

        - Execute a simple command with an absolute path like /bin/ls or any other command with arguments but without
        quotes and double quotes then execute echo $?
        - Check the printed value. You can repeat the same in bash and compare it.
        - Repeat multiple times with different commands and arguments, use some failing commands like '/bin/ls
        filethatdoesntexist'
        - anything like expr $? + $?
        - if something crashes use the crash flag.
        - if something is not working use the incomplete work flag.


- [ ] Signals

      - Try ctrl-C in an empty prompt should show a new line with a new prompt
      - Try ctrl-\ in an empty prompt should not do anything
      - Try ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
      - Try ctrl-C in a prompt after you wrote some stuff should show a new line with a new prompt
      - Try ctrl-D in a prompt after you wrote some stuff should not do anything
      - Try ctrl-\ in a prompt after you wrote some stuff should quit minishell --> RELAUNCH!
      - Try ctrl-C after running a blocking command like cat or grep without arguments
      - Try ctrl-\ after running a blocking command like cat or grep without arguments
      - Try ctrl-D after running a blocking command like cat or grep without arguments
      - Repeat multiple times with different commands
      - if something crashes use the crash flag.
      - if something is not working use the incomplete work flag.


- [ ] Double Quotes

      - Execute commands with simple quotes as an argument
      - Try empty arguments
      - Try environment variables, whitespaces, pipes, redirection in the simple quotes
      - echo '$USER' must print $USER
      - Nothing should be interprated

- [ ] env

      - Check if env shows you the current environment variables

- [ ] export
    
      - Export environment variables, create new ones, and replace old ones
      - Check them with env

- [ ] unset
    
      - Export environment variables, create new ones, and replace old ones
      - Use unset to remove some of them
      - Check the result with env


- [ ] cd
    
      - Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
      - Repeat multiple times with working and not working cd
      - try '.' '..' as arguments too


- [ ] pwd
 
      - Use the command pwd
      - Repeat multiple times in multiple directories

  
- [ ] Relative Path

      - Execute commands but this time use a relative path
      - Repeat multiple times in multiple directories with a complex relative path (lots of ..)
      - Execute commands but this time without any path. (ls, wc, awk etc...)
      - Unset the $PATH and check if it is not working anymore
      - Set the $PATH to a multiple directory value (directory1:directory2) and check that directories are checked in order
        from left to right

- [ ] Redirection
    
      - Execute commands with redirections < and/or >
      - Repeat multiple times with different commands and arguments and sometimes change > with >>
      - Check if multiple of the same redirections fail
      - Test << redirection (it doesn't need to update history).


- [ ] Pipes

      - Execute commands with pipes like 'cat file | grep bla | more'
      - Repeat multiple times with different commands and arguments
      - Try some failing commands like 'ls filethatdoesntexist | grep bla | more'
      - Try to mix pipes and redirections.


- [ ] Go Crazy and history
      
      - type a command line then use ctrl-C then press enter the buffer should be clean and nothing try to execute.
      - Can we navigate through history with up and down and retry some command
      - Execute commands that should not work like 'dsbksdgbksdghsd' and check if the shell doesn't crash and prints an
        error
      - Try to execute a long command with a ton of arguments
      - Have fun with that beautiful minishell and enjoy it


- [ ] Environment Variables

      - Execute echo with some $ variables as argumentss
      - Check that $ is interprated as an environment variable
      - Check that double quotes interpolate $
      - Check that $USER exist or set it.
      - echo "$USER" should print the value of $USER

BONUS

- [ ] And, Or

      - Use &&, || and parenthesis with commands and check if it works as bash


- [ ] WildCard

       - Use wildcards in arguments for the local directory.


- [ ] Surprise (or not...)
      
      - set USER environment variable.
      - Test echo "'$USER'" this should print 'USER_VALUE'
      - Test echo '"$USER"' this should print "$USER"




![144017004-aa68e8d7-5da7-4ece-afc6-b8ab100113df](https://github.com/tentaclepurple/Minishell/assets/116112114/c8a7150d-eb99-4cf0-bfec-85792c8dd939)
![144017016-ef2bb606-c301-42c6-88f1-8ed4339d22cd](https://github.com/tentaclepurple/Minishell/assets/116112114/c6bc01d7-6262-49c3-b946-6104c2089dab)
