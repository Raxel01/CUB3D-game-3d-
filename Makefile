# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 03:18:17 by abait-ta          #+#    #+#              #
#    Updated: 2023/12/08 15:38:09 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING_D = ./PARSING/Displayer
PARSING_G = ./PARSING/General_tools
PARS_L    = ./PARSING/getline
PARS_M    = ./PARSING/MAPARSER
PARS_COL  = ./PARSING/Importcolors
PARS_TEXT = ./PARSING/Importtextures
PARS_MEM  = ./PARSING/Memory_clean
RUN_GAME  = ./RunGame

RUN_GAME_SRC = $(RUN_GAME)/rungame.c $(RUN_GAME)/keys.c $(RUN_GAME)/start.c $(RUN_GAME)/start_utils.c \
				$(RUN_GAME)/gets.c $(RUN_GAME)/update.c $(RUN_GAME)/moves_functions.c \
				$(RUN_GAME)/check_utils.c $(RUN_GAME)/init_functions.c $(RUN_GAME)/turn_functions.c \
				$(RUN_GAME)/cast_rays.c $(RUN_GAME)/wall_rendring.c $(RUN_GAME)/textures.c $(RUN_GAME)/h_and_v_wall.c

SRC = Global_main.c $(PARSING_D)/display_errors.c $(PARSING_G)/g_tools.c $(PARSING_G)/g_usage.c \
$(PARSING_G)/g_utils.c $(PARS_L)/get_next_line.c $(PARS_L)/get_next_line_utils.c $(PARS_TEXT)/textures_builder.c \
$(PARSING_G)/g_epurline.c $(PARS_COL)/extractcolor.c $(PARS_COL)/rgbchecker.c $(PARS_TEXT)/extractextures.c \
$(PARS_TEXT)/sequelextract.c $(PARS_MEM)/claimmemory.c $(PARS_M)/border_begin.c $(PARS_M)/border_analyser.c \
$(PARS_M)/border_end.c $(PARS_M)/elemmap_analyser.c $(PARS_M)/map_extraction.c $(PARS_M)/validacces.c \
$(PARS_M)/validacces_sequel.c $(PARS_TEXT)/onlyrequired.c  $(RUN_GAME_SRC)

HEADER = ./HEADER/Parsing.h ./HEADER/game.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ofast

MLX_FLAGS = -framework OpenGL -framework AppKit

OBJ = ${SRC:.c=.o}

NAME = cub3D

all : $(NAME)

$(NAME): $(HEADER) $(OBJ)
	$(CC) $(CFLAGS) $(MLX_FLAGS) ~/minilibx/libmlx.a -o $@ $(OBJ)

%.o : %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $<  -o  $@ 

clean :
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all

norm :
		norminette

.PHONY: clean fclean all re NAME