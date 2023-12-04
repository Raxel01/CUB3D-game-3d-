# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 03:18:17 by abait-ta          #+#    #+#              #
#    Updated: 2023/12/04 13:16:13 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING_D = ./PARSING/Displayer
PARSING_G = ./PARSING/General_tools
PARS_L    = ./PARSING/getline
PARS_M    = ./PARSING/MAPARSER
PARS_COL  = ./PARSING/Importcolors
PARS_TEXT = ./PARSING/Importtextures
PARS_MEM  = ./PARSING/Memory_clean

SRC = Global_main.c $(PARSING_D)/display_errors.c $(PARSING_G)/g_tools.c $(PARSING_G)/g_usage.c \
$(PARSING_G)/g_utils.c $(PARS_L)/get_next_line.c $(PARS_L)/get_next_line_utils.c $(PARS_TEXT)/textures_builder.c \
$(PARSING_G)/g_epurline.c $(PARS_COL)/extractcolor.c $(PARS_COL)/rgbchecker.c $(PARS_TEXT)/extractextures.c \
$(PARS_TEXT)/sequelextract.c $(PARS_MEM)/claimmemory.c $(PARS_M)/border_begin.c $(PARS_M)/border_analyser.c \
$(PARS_M)/border_end.c $(PARS_M)/elemmap_analyser.c $(PARS_M)/map_extraction.c $(PARS_M)/validacces.c \
$(PARS_M)/validacces_sequel.c
 
HEADER = ./HEADER/Parsing.h

CC = cc

FLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

NAME = cub3D

all : $(NAME)

$(NAME): $(HEADER) $(OBJ)
	@$(CC) $(CFLAGS)  -o  $@ $(OBJ)

%.o : %.c $(HEADER)
	@$(CC)  $(CFLAGS) -c $<  -o  $@

clean :
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

norm :
		norminette
sound :
	open ~/Downloads/Assassin\'s\ Creed\ Origins\ \(OST\)\ -\ Legions\ of\ Blood.mp3

Egypt : clean sound 
	clear && ./$(NAME) maps/egypt.cub
	
.PHONY: clean fclean all re NAME