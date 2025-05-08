.SILENT:

#Flags

CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g

#Files

FILES= $(SRC_DIR)/???.c \

OBJS=$(FILES:.c=.o)

#Directories

SRC_DIR=src

#Includes

NAME=???
LIBFT=./includes/libft/libft.a

#Decoration

CYAN = \033[1;36m
GREEN = \033[1;32m
RED = \031[1;31m
RESET = \033[0m
BOX_TOP = /===============\\
BOX_MID = |
BOX_MID_END = |
BOX_BOT = \\===============/

#Compilation

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(RED)Making ??? ...$(RESET)"
	@gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(GREEN)??? Done Succesfully !$(RESET)"


$(LIBFT):
	@make -C ./includes/libft --no-print-directory

%.o: %.c
	@gcc $(CFLAGS) -I includes -c $< -o $@

#Commands

all: $(NAME)
	@echo "$(GREEN)All Done Succesfully !$(RESET)"
	@echo "$(CYAN)$(BOX_TOP) $(RESET)"
	@echo "$(CYAN)$(BOX_MID)$(RESET)$(GREEN)Executable Done$(RESET)$(CYAN)$(BOX_MID_END)$(RESET)"
	@echo "$(CYAN)$(BOX_BOT)$(RESET)"

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
