# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 09:41:00 by cmenke            #+#    #+#              #
#    Updated: 2023/07/25 14:24:17 by wmoughar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ar -r ->replace exising files or create a new one if. 
#ar -c -> silence the information message.
#ar -s -> adds or updates an onject-file index to the archive.

NAME := libft.a

SRC := ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_printf.c \
	get_next_line_bonus.c \
	ft_strcmp.c

OBJS := ${SRC:.c=.o}

HEADER := libft.h

CC := cc

# CFLAGS := -Wall -Werror -Wextra -g -O0 #-fsanitize=address

all :	${NAME}

${NAME}: ${OBJS}
	ar -rc ${NAME} ${OBJS}

$(OBJS): ${HEADER}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

.NOTPARALLEL:
