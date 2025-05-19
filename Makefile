.SILENT:

#Flags

CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g -lreadline

#Files

FILES= $(SRC_DIR)/exec/minishell.c $(SRC_DIR)/exec/exec.c $(SRC_DIR)/exec/minishell_utils.c \
	$(SRC_DIR)/pars/minishell_pars.c \

OBJS=$(FILES:.c=.o)

#Directories

SRC_DIR=src

#Includes

NAME=Minishell
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
	@echo "$(CYAN)  __    __   ___________    ____       $(RESET)$(GREEN)   _______. __    __   _______  __       __      $(RESET)";
	@echo "$(CYAN) |  |  |  | |   ____\   \  /   /       $(RESET)$(GREEN)  /       ||  |  |  | |   ____||  |     |  |     $(RESET)";
	@echo "$(CYAN) |  |__|  | |  |__   \   \/   / ______ $(RESET)$(GREEN) |   (----\`|  |__|  | |  |__   |  |     |  |     $(RESET)";
	@echo "$(CYAN) |   __   | |   __|   \_    _/ |______|$(RESET)$(GREEN)  \   \    |   __   | |   __|  |  |     |  |     $(RESET)";
	@echo "$(CYAN) |  |  |  | |  |____    |  |         $(RESET)$(GREEN).----)   |   |  |  |  | |  |____ |  \`----.|  \`----.$(RESET)";
	@echo "$(CYAN) |__|  |__| |_______|   |__|         $(RESET)$(GREEN)|_______/    |__|  |__| |_______||_______||_______|$(RESET)";
	@echo "$(CYAN)                                                                                      $(RESET)";


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
