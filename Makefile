# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 03:18:17 by abait-ta          #+#    #+#              #
#    Updated: 2023/11/12 20:30:31 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING = ./PARSING

SRC = Global_main.c $(PARSING)/display_errors.c $(PARSING)/General_tools/g_tools.c \

HEADER = ./HEADER/Parsing.h

CC = cc

FLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

NAME = cub3d

all : $(NAME)

$(NAME): $(HEADER) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ -fsanitize=address -g $(OBJ)

%.o : %.c $(HEADER)
	@$(CC)  $(CFLAGS) -c -fsanitize=address -g $< -o  $@	

clean :
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

norm :
		norminette

.PHONY: clean fclean all re NAME