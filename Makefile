
NAME        = 	minishell

# Directories
SRCS_DIR	=	srcs
INCLUDES_DIR=	includes
DIR_OBJ		=	obj
LIBFT_DIR	=	LIBFT

# Compiler
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDES_DIR) -I$(LIBFT_DIR)

# Libraries
LIBFT_A		=	$(LIBFT_DIR)/libft.a

SRC	=	srcs/main.c\
		srcs/split_and_init_pipelines.c\
		srcs/ft_split_op.c\
		srcs/make_pipeline.c\
		srcs/clean_line.c\
		srcs/cleaning_parsing.c\
		srcs/alias_expansion.c\
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
		srcs/get_readline.c\
		srcs/utils_parsing.c\
		srcs/find_file.c\
		srcs/update_lst.c\
		srcs/exec.c \
		srcs/red_in.c \
		srcs/built_in/cd.c \
		srcs/built_in/unset.c \
		srcs/built_in/echo.c \
		srcs/built_in/env.c \
		srcs/built_in/export.c \
# 		srcs/red_out.c \

OBJS	=	$(SRC:%.c=%.o)

all: $(LIBFT_A) $(NAME) 

$(LIBFT_A): $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

$(NAME): $(LIBFT_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME) 


%.o: %.c $(INCLUDES_DIR)/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ${OBJS}
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re