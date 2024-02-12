# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vamologl <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 11:54:04 by vamologl          #+#    #+#              #
#    Updated: 2023/04/26 10:30:31 by vamologl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
LDFLAGS=-L.
LDLIBS=-ltf

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_strlen.c ft_memset.c \
	ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
	ft_tolower.c ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_isascii.c ft_strrchr.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strchr.c ft_strtrim.c ft_substr.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_strncpy.c \

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) -I. -o $@ -c $? $(CFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)
	$(RM) $(OBJS)

re: fclean all

are: clean fclean all
