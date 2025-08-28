# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 19:21:54 by mlagniez          #+#    #+#              #
#    Updated: 2025/08/26 15:50:54 by mlagniez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SOURCES	= ${LIBFT_CLASSICS} ${FT_PRINTF} ${GNL}

LIBFT_CLASSICS = classics/ft_strlen.c\
			classics/ft_strncmp.c\
			classics/ft_atoi.c\
			classics/ft_bzero.c\
			classics/ft_isalnum.c\
			classics/ft_isalpha.c\
			classics/ft_isascii.c\
			classics/ft_isdigit.c\
			classics/ft_isprint.c\
			classics/ft_memchr.c\
        	classics/ft_memcmp.c\
			classics/ft_memcpy.c\
			classics/ft_memmove.c\
			classics/ft_memset.c\
			classics/ft_strchr.c\
			classics/ft_strlcat.c\
			classics/ft_strlcpy.c\
			classics/ft_strnstr.c\
        	classics/ft_strrchr.c\
			classics/ft_tolower.c\
			classics/ft_toupper.c\
			classics/ft_calloc.c\
			classics/ft_strdup.c\
			classics/ft_substr.c\
			classics/ft_strjoin.c\
			classics/ft_strtrim.c\
			classics/ft_split.c\
			classics/ft_itoa.c\
			classics/ft_strmapi.c\
			classics/ft_striteri.c\
			classics/ft_putchar_fd.c\
			classics/ft_putstr_fd.c\
			classics/ft_putendl_fd.c\
			classics/ft_putnbr_fd.c
			
FT_PRINTF = 	ft_printf/ft_printf.c\
			ft_printf/four_winds.c
			
GNL =		gnl/get_next_line_bonus.c\
			gnl/get_next_line_utils_bonus.c

BONUS	=	lists/ft_lstnew_bonus.c\
			lists/ft_lstadd_front_bonus.c\
			lists/ft_lstsize_bonus.c\
			lists/ft_lstlast_bonus.c\
			lists/ft_lstadd_back_bonus.c\
			lists/ft_lstdelone_bonus.c\
			lists/ft_lstclear_bonus.c\
			lists/ft_lstiter_bonus.c\
			lists/ft_lstmap_bonus.c
			

OBJECTS	=${SOURCES:.c=.o}

BONUS_O = ${BONUS:.c=.o}

all: ${NAME} 

${NAME} : ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

bonus: ${OBJECTS} ${BONUS_O}
	ar rcs ${NAME} ${OBJECTS} ${BONUS_O}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ -I includes

clean:
	rm -f ${OBJECTS} ${BONUS_O}

fclean:	clean
	rm -f ${NAME}

re:		fclean all

.PHONY:	all clean fclean re bonus