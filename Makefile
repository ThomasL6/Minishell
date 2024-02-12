# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vamologl <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 11:11:30 by vamologl          #+#    #+#              #
#    Updated: 2024/01/23 11:11:34 by vamologl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
NAME = Minishell
CFLAGS = -Wall -Wextra -Werror -g3

FLAGLFT = -Llibft -lft

SRCS = main.c \
	exit.c \
	parse/ft_separ.c \
	parse/parser_error.c \
	parse/parser_utils2.c \
	parse/parser.c \
	parse/parser_utils.c \
	utils.c \
	utils2.c \
	check/c_quote.c \
	check/c_pipes.c \
	lists/listchained.c \
	lists/listchained2.c \
	builtin/ft_pwd.c \
	builtin/ft_cd.c \
	builtin/ft_echo.c \
	user.c \


OBJS = $(SRCS:.c=.o)

all : $(NAME)

alldb : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	$(MAKE) clean -C libft
	@echo "clean"

clear :
	rm -f $(OBJS)
	$(MAKE) clear -C libft
	@echo "clear"


#------------------------------------
fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	@echo "fclean"


fclear : clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	@echo "fclear"

#------------------------------------


re : fclean all


$(NAME) : $(OBJS)
	@make -C libft
	$(CC)  $(OBJS) -o $(NAME) -Iinclude $(FLAGLFT) -lreadline -g3
	@echo "Re"

.PHONY : all clean fclean re
 
.SILENT:

