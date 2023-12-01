# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tben-dal <tben-dal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 03:18:17 by abait-ta          #+#    #+#              #
#    Updated: 2023/12/01 16:32:04 by tben-dal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING_D = ./PARSING/Displayer
PARSING_G = ./PARSING/General_tools
PARS_L    = ./PARSING/getline
PARS_M    = ./PARSING/MAPARSER
PARS_COL  = ./PARSING/Importcolors
PARS_TEXT = ./PARSING/Importtextures
PARS_MEM  = ./parsing/Memory_clean
RUN_GAME  = ./RunGame

RUN_GAME_SRC = $(RUN_GAME)/rungame.c $(RUN_GAME)/keys.c $(RUN_GAME)/start.c $(RUN_GAME)/start_utils.c \
				$(RUN_GAME)/drawFunction.c $(RUN_GAME)/gets.c $(RUN_GAME)/update.c $(RUN_GAME)/moves_functions.c \
				$(RUN_GAME)/check_utils.c $(RUN_GAME)/init_functions.c $(RUN_GAME)/turn_functions.c \
				$(RUN_GAME)/cast_all_rays.c

SRC = Global_main.c $(PARS_M)/import_map.c $(PARSING_D)/display_errors.c $(PARSING_G)/g_tools.c $(PARSING_G)/g_usage.c \
$(PARSING_G)/g_utils.c $(PARS_L)/get_next_line.c $(PARS_L)/get_next_line_utils.c $(PARS_M)/textures_builder.c \
$(PARSING_G)/g_epurline.c $(PARS_COL)/extractcolor.c $(PARS_COL)/rgbchecker.c $(PARS_TEXT)/extractextures.c \
$(PARS_TEXT)/sequelextract.c $(PARS_MEM)/claimmemory.c $(RUN_GAME_SRC)
 

HEADER = ./HEADER/Parsing.h ./HEADER/game.h

CC = cc

FLAGS = -Wall -Wextra -Werror -g -Ofast

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

OBJ = ${SRC:.c=.o}

NAME = cub3d

all : $(NAME)

$(NAME): $(HEADER) $(OBJ)
	@$(CC) $(CFLAGS) $(MLX_FLAGS)  -o  $@ $(OBJ)

%.o : %.c $(HEADER)
	@$(CC)  $(CFLAGS) -c $<  -o  $@ 

clean :
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

norm :
		norminette

.PHONY: clean fclean all re NAME