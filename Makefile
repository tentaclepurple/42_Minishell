NAME = minishell
NAMEBONUS = minishell_bonus
LIBNAME = libft.a
SRC = 	./src/splitstr/split.c \
		./src/splitstr/split_utils.c \
		./src/splitstr/clean_quotes.c \
		./src/splitstr/check_var.c  \
		./src/splitstr/check_var2.c  \
		./src/splitstr/check_files.c  \
		./src/splitstr/correc_special.c \
		./src/parser/parser.c \
		./src/parser/executor.c \
		./src/parser/heredoc.c \
		./src/parser/getpaths.c \
		./src/parser/parser_util.c \
		./src/parser/parser_util2.c \
		./src/terminal/terminal.c \
		./src/terminal/terminal_aux.c \
		./src/main.c \
		./src/error/error.c \
		./src/envutils/envcp.c \
		./src/builtins/bt_cd.c \
		./src/builtins/bt_env_pwd_echo.c \
		./src/builtins/bt_export.c \
		./src/builtins/bt_unset.c \
		./src/builtins/btmanager.c \
		./src/builtins/bt_exit.c
SRCBONUS = 	./src/splitstr/split_bonus.c \
		./src/splitstr/split_utils.c \
		./src/splitstr/clean_quotes.c \
		./src/splitstr/check_var.c  \
		./src/splitstr/check_var2.c  \
		./src/splitstr/correc_special.c \
		./src/splitstr/check_files.c  \
		./src/parser/parser_bonus.c \
		./src/parser/executor_bonus.c \
		./src/parser/heredoc_bonus.c \
		./src/parser/getpaths_bonus.c \
		./src/parser/parser_util_bonus.c \
		./src/parser/parser_util2_bonus.c \
		./src/parser/wildcard_bonus.c \
		./src/parser/wildcard_aux_bonus.c \
		./src/terminal/terminal_bonus.c \
		./src/terminal/terminal_aux_bonus.c \
		./src/main.c \
		./src/error/error.c \
		./src/envutils/envcp.c \
		./src/builtins/bt_cd.c \
		./src/builtins/bt_env_pwd_echo.c \
		./src/builtins/bt_export.c \
		./src/builtins/bt_unset.c \
		./src/builtins/btmanager.c \
		./src/builtins/bt_exit.c

OBJ = $(SRC:.c=.o)
OBJBONUS = $(SRCBONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
READFLAG =  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
READINCLUDE = -I/Users/$(USER)/.brew/opt/readline/include
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ) $(LIBNAME)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS)   $(OBJ) $(LIBNAME) $(READFLAG)  -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

bonus: $(OBJBONUS) $(LIBNAME)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAMEBONUS)..." $(NONE)
	@gcc $(FLAGS)   $(OBJBONUS) $(LIBNAME) $(READFLAG)  -o $(NAMEBONUS)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(LIBNAME):
	@echo $(CURSIVE)$(GRAY) "     - Compiling LIBFT $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ./libft all
	@cp ./libft/libft.a $(LIBNAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

%.o: %.c
	$(CC) $(READINCLUDE) -c $(FLAGS) $^ -o $@

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@$(MAKE) -C ./libft clean
	@rm -rf $(OBJ) $(OBJBONUS)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME) And $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ./libft fclean
	@rm -rf $(NAME)  $(NAMEBONUS) $(LIBNAME)

re: fclean all

.PHONY: all bonus clean fclean re