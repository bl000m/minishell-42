# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 14:44:01 by mpagani           #+#    #+#              #
#    Updated: 2023/02/21 15:57:48 by mpagani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

# mandatory srcs / obj files
SRCS 		= main.c communicating.c here_doc.c memory_stuff.c parsing.c settings.c \
			error_management.c utils.c prompt.c lexer.c lexer_token_counting.c \
			lexer_token_splitting.c \
			lexer_utils.c

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

all: obj $(LIBFT) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT_LNK) -o $(NAME) -lreadline

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c Makefile $(INCS_DIR)/minishell.h
	$(CC) $(CFLAGS) $(LIBFT_INC) -I $(INCS_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

#force ?

clean:
	$(RM) $(OBJDIR)
	$(RM) $(OBJ_BON_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(NAME)_bonus

re: fclean all

.PHONY: all clean fclean re
