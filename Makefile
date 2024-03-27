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

CC = cc 
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3

FLAGLFT = -Llibft -lft

SRCS = main.c \
	exit.c \
	builtin/export/ft_export.c \
	builtin/export/export_utils.c \
	builtin/export/export_utils1.c \
	builtin/ft_pwd.c \
	builtin/ft_cd.c \
	builtin/ft_echo.c \
	builtin/ft_unset.c \
	builtin/ft_env.c \
	check/c_quote.c \
	check/c_pipes.c \
	exec/exec.c \
	exec/exec2.c\
	lists/listchained.c \
	lists/listchained2.c \
	parse/parser.c \
	parse/parser_error.c \
	parse/parser_utils.c \
	parse/parser_utils2.c \
	parse/parser_utils3.c \
	parse/parser_utils4.c\
	parse/parser_utils5.c\
	parse/token.c \
	parse/token2.c \
	redir_pipe/gest_redir.c \
	redir_pipe/gest_pipeline.c\
	redir_pipe/gest_redir_utils.c \
	redir_pipe/gest_redir_utils1.c \
	Utils/utils.c \
	Utils/utils2.c \
	Utils/utils3.c \
	user.c \
	parse/init_input_parser.c \
	parse/init_input_parser2.c \


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

