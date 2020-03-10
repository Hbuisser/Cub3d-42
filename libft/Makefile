# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 12:18:16 by hbuisser          #+#    #+#              #
#    Updated: 2020/03/10 17:10:31 by hbuisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I$(HEADER)

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_free.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
ft_toupper.c ft_strncpy.c ft_strcmp.c
SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstclear_bonus.c \
ft_lstdelone_bonus.c ft_lstiter_bonus.c
OBJECTS = $(SRCS:%.c=%.o)
OBJECTS_B = $(SRCS_B:%.c=%.o)
CC = gcc
REM = rm -rf
HEADER = ./

all: $(NAME)
$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	ranlib $(NAME)
$(OBJECTS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
$(OBJECTS_B): $(SRCS_B)
	$(CC) $(CFLAGS) -c $(SRCS_B)
bonus: fclean $(OBJECTS) $(OBJECTS_B)
	ar rcs libft.a $(OBJECTS) $(OBJECTS_B)
clean:
	$(REM) $(OBJECTS) $(OBJECTS_B)
fclean: clean
	$(REM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
