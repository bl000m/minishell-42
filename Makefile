# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 14:44:01 by mpagani           #+#    #+#
#    Updated: 2023/02/21 16:34:58 by fbelfort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

# mandatory srcs / obj files
SRCS 		= main.c \
			env_utils.c \
     		user/prompt.c \
			user/here_doc.c \
			parsing/lexer.c \
      		parsing/lexer_token_counting.c \
			parsing/lexer_token_splitting.c \
			parsing/lexer_utils.c \
      		parsing/lexer_expand.c \
			parsing/parsing.c \
			settings_utils/memory_stuff.c \
			settings_utils/settings.c \
			settings_utils/error_management.c \
      		settings_utils/utils.c \
			exec/communicating.c \
			exec/builtins.c

OBJS 		= $(SRCS:%.c=$(OBJDIR)/%.o)

# compile
CC 			= cc
CFLAGS 		= -Wall -Werror -Wextra

# directories
SRCS_DIR	= ./srcs
INCS_DIR	= ./includes
OBJDIR 		= ./obj

# library ft_
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_INC	= -I ./libft
LIBFT_LNK	= -L ./libft -l ft

# others
RM 			= rm -rf

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/exec
	mkdir -p $(OBJDIR)/parsing
	mkdir -p $(OBJDIR)/user
	mkdir -p $(OBJDIR)/settings_utils

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT_LNK) -o $(NAME) -lreadline

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c Makefile $(INCS_DIR)/minishell.h $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT_INC) -I $(INCS_DIR) -c $< -o $@

$(LIBFT):	FORCE
	make -C $(LIBFT_DIR)

FORCE	:

clean:
	$(RM) $(OBJDIR)
	$(RM) $(OBJ_BON_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(NAME)_bonus

re: fclean all

.PHONY: all clean fclean re FORCE
