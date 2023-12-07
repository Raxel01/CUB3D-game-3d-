# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 03:18:17 by abait-ta          #+#    #+#              #
#    Updated: 2023/12/07 13:53:45 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING_D = ./PARSING/Displayer
PARSING_G = ./PARSING/General_tools
PARS_L    = ./PARSING/getline
PARS_M    = ./PARSING/MAPARSER
PARS_COL  = ./PARSING/Importcolors
PARS_TEXT = ./PARSING/Importtextures
PARS_MEM  = ./PARSING/Memory_clean
BN = ./Bonus

SRC = Global_main.c $(PARSING_D)/display_errors.c $(PARSING_G)/g_tools.c $(PARSING_G)/g_usage.c \
$(PARSING_G)/g_utils.c $(PARS_L)/get_next_line.c $(PARS_L)/get_next_line_utils.c $(PARS_TEXT)/textures_builder.c \
$(PARSING_G)/g_epurline.c $(PARS_COL)/extractcolor.c $(PARS_COL)/rgbchecker.c $(PARS_TEXT)/extractextures.c \
$(PARS_TEXT)/sequelextract.c $(PARS_MEM)/claimmemory.c $(PARS_M)/border_begin.c $(PARS_M)/border_analyser.c \
$(PARS_M)/border_end.c $(PARS_M)/elemmap_analyser.c $(PARS_M)/map_extraction.c $(PARS_M)/validacces.c \
$(PARS_M)/validacces_sequel.c $(PARS_TEXT)/onlyrequired.c $(RUN_GAME_SRC)

BNSRC = $(BN)/mouse_bonus.c

HEADER = ./HEADER/Parsing.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -framework OpenGL -framework AppKit

OBJ = ${SRC:.c=.o}

OBJ_BN = ${BNSRC:.c=.o}

NAME = cub3D

all : $(NAME)

$(NAME): $(HEADER) $(OBJ)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o  $@ $(OBJ)

%.o : %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $<  -o  $@ 

bonus: $(HEADER) $(OBJ_BN)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o  $@ $(OBJ_BN)

clean :
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all

norm :
		norminette

.PHONY: clean fclean all re NAME