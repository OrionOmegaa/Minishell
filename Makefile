.SILENT:

#Flags

CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g -lreadline

#Files

FILES= $(EXEC)/builtin_utils.c $(EXEC)/builtin.c $(EXEC)/exec_build.c \
	$(EXEC)/exec_child.c  $(EXEC)/exec_init.c $(EXEC)/exec_parent.c  \
	$(EXEC)/exec_pipeline_bool.c $(EXEC)/exec_pipeline.c $(EXEC)/open.c \
	$(EXEC)/minishell_utils.c $(EXEC)/minishell.c $(EXEC)/node.c \
	$(INIT)/free.c $(INIT)/init.c $(INIT)/pars_single_cmd_redir.c \
	$(INIT)/pars_single_cmd_utils.c $(INIT)/pars_single_cmd.c \
	$(INIT)/parse_line.c $(INIT)/redirection.c $(INIT)/split_pipes_iter.c \
	$(INIT)/split_pipes_utils.c $(INIT)/split_pipes.c \
	$(INIT)/syntax_checks.c $(INIT)/syntax_utils.c $(INIT)/syntax.c \
	$(PARS)/env_set_utils.c $(PARS)/env_set.c $(PARS)/expansion_core.c \
	$(PARS)/expansion_env.c $(PARS)/expansion_utils.c \
	$(PARS)/extract_args.c $(PARS)/fd.c $(PARS)/find_path.c \
	$(PARS)/minishell_pars.c $(PARS)/signal.c 

OBJS=$(FILES:.c=.o)

#Directories
EXEC=src/exec
INIT=src/init
PARS=src/pars

#Includes

NAME=minishell
LIBFT=./includes/libft/libft.a

#Decoration

CYAN = \033[1;36m
GREEN = \033[1;32m
RED = $(shell tput setaf 1)
RESET = $(shell tput sgr0)
BOX_TOP = /===============\\
BOX_MID = |
BOX_MID_END = |
BOX_BOT = \\===============/

#Compilation

$(NAME): $(OBJS) $(LIBFT)
	@gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(CYAN)  __    __   ___________    ____          _______. __    __   _______  __       __      ";
	@echo " |  |  |  | |   ____\   \  /   /         /       ||  |  |  | |   ____||  |     |  |     ";
	@echo " |  |__|  | |  |__   \   \/   / ______  |   (----\`|  |__|  | |  |__   |  |     |  |     ";
	@echo " |   __   | |   __|   \_    _/ |______|  \   \    |   __   | |   __|  |  |     |  |     ";
	@echo " |  |  |  | |  |____    |  |         .----)   |   |  |  |  | |  |____ |  \`----.|  \`----.";
	@echo " |__|  |__| |_______|   |__|         |_______/    |__|  |__| |_______||_______||_______|";
	@echo "                                                                                      $(RESET)";


$(LIBFT):
	@make -C ./includes/libft --no-print-directory

%.o: %.c
	@gcc $(CFLAGS) -I includes -c $< -o $@

#Commands

all: $(NAME)

clean:
	@echo "$(RED)Cleaning object file in progress ...$(RESET)"
	@rm -f $(OBJS)
	@make clean -C ./includes/libft --no-print-directory
	@echo "$(GREEN)CLEAN Done Succesfully !$(RESET)"

fclean: clean
	@echo "$(RED)Full Clean in progress ...$(RESET)"
	@rm -f $(NAME)
	@make fclean -C ./includes/libft --no-print-directory
	@echo "$(GREEN)FCLEAN Done Succesfully !$(RESET)"

re: fclean all

#phony

.PHONY: all clean fclean re
