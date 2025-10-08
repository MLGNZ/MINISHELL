NAME        = minishell

SRC_DIR     = srcs
LIBFT_DIR   = LIBFT
BUILD_DIR   = build

INC         = includes

CC          = cc
CFLAGS      =  -g3 -I$(INC) -I$(LIBFT_DIR)
LDFLAGS 	= -lreadline -lncurses

# -Wall -Wextra -Werror

LIBFT_A     = $(LIBFT_DIR)/libft.a

SRC	=	srcs/nothing.c \
		srcs/main.c\
		srcs/split_and_init_pipelines.c\
		srcs/split_and_init_pipelines2.c\
		srcs/ft_split_op.c\
		srcs/make_pipeline.c\
		srcs/make_pipeline2.c\
		srcs/clean_line.c\
		srcs/clean_line2.c\
		srcs/cleaning_parsing.c\
		srcs/alias_expansion.c\
		srcs/alias_expansion2.c\
		srcs/alias_expansion3.c\
		srcs/ft_strjoin_free1.c\
		srcs/split_lines.c\
		srcs/parse_error_near.c\
		srcs/dive_into_lines.c\
		srcs/join_split.c\
		srcs/update_split.c\
		srcs/dup_split.c\
		srcs/update_split_just_replace.c\
		srcs/ft_strnjoin.c\
		srcs/go_to_subshell.c\
		srcs/panic.c\
		srcs/exec_line.c\
		srcs/utils.c\
		srcs/utils2.c\
		srcs/get_readline.c\
		srcs/utils_parsing.c\
		srcs/find_file.c\
		srcs/update_lst.c\
		srcs/exec.c \
		srcs/built_in/cd.c \
		srcs/built_in/unset.c \
		srcs/built_in/echo.c \
		srcs/built_in/env.c \
		srcs/built_in/export.c \
		srcs/redirs/fd_n_pipe.c \
		srcs/redirs/fds.c \
		srcs/redirs/red_out.c \
		srcs/redirs/red_in.c \
		srcs/wildcards.c \
		srcs/wildcards2.c \
		srcs/exec_built_in.c \
		srcs/errors_utils.c \
		srcs/signal.c \
		srcs/ft_split_reexpand.c

OBJ         = $(addprefix $(BUILD_DIR)/, $(subst $(SRC_DIR)/,,$(SRC:.c=.o)))

# ================================[ Couleurs ]================================

GREEN       = \033[0;32m
BLUE        = \033[0;34m
BLUE        = \033[1;34m
END         = \033[0m
TITLE       = \033[1m
BG_GREEN    = \033[42m
UNDERLINE   = \033[4m
GREY_LIGHT  = \033[38;5;250m


BOLD        = \033[1m

# ================================[ Règles Make ]==============================

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@echo "WELCOME TO THE BIGGEST GIGA SHELL" | toilet 
	@echo "$(GREY_LIGHT)🔘 $(UNDERLINE)$(TITLE)make $(NAME)$(END)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $(NAME) && \
	echo "   $(BLUE)⤷ $(END)Executable: $(BG_GREEN)$(BOLD)$(NAME)$(END)"

$(LIBFT_A):
	@echo "$(GREY_LIGHT)🔘 $(UNDERLINE)$(TITLE)compiling libft... $(END)"
	@make -s -C $(LIBFT_DIR) bonus && echo "   $(BLUE)⤷ $(END)Success $(GREEN)(libft.a)$(END)"


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@if [ -z "$$(ls -A $(BUILD_DIR) 2>/dev/null)" ]; then \
		echo "$(GREY_LIGHT)🔘 $(UNDERLINE)$(TITLE)Create object files$(END)"; fi
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null && \
	printf "   $(BLUE)⤷ $(GREEN)%-38s $(BLUE)-->  $(GREEN)%s$(END)\n" "$<" "$@"

# ================================[ Nettoyage ]===============================

c clean:
	@echo "$(GREY_LIGHT)🔘 $(UNDERLINE)$(TITLE)make clean$(END)"
	@rm -f $(OBJ) && echo "   $(BG_WHITE)⤷ $(END)Removed object files"
	@make -s -C $(LIBFT_DIR) clean
	
fc fclean:
	@echo "$(GREY_LIGHT)🔘 $(UNDERLINE)$(TITLE)make fclean$(END)"
	@if [ -f $(NAME) ]; then rm -f $(NAME) && echo "   $(BLUE)⤷ $(END)Removed binary $(NAME)"; fi
	@if [ -d $(BUILD_DIR) ]; then rm -rf $(BUILD_DIR) && echo "   $(BLUE)⤷ $(END)Removed build dir"; fi
	@make -s -C $(LIBFT_DIR) fclean


re: fc all

.PHONY: all clean c fclean fc re
