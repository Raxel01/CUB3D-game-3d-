/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:59:43 by abait-ta          #+#    #+#             */
/*   Updated: 2023/12/04 15:50:49 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADER/Parsing.h"

void	game_usage(void)
{
	write(1, "*===================================*\n", 38);
	write(1, "*           -::USAGE::-             *\n", 38);
	sleep(1);
	write(1, "*=[EXECUTABLE] [av(1) : PATH_TO_MAP]*", 37);
	sleep(1);
	write(1, "\n*      W : avancez * S : reculez    *\n", 39);
	sleep(1);
	write(1, "*      D : A Droit * S : A gauche   *\n", 38);
	sleep(1);
	write(1, "*===================================*\n", 38);
}

void	display_error(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	extension_error(void)
{
	write(STDERR_FILENO, "/*\n", 3);
	write(STDERR_FILENO, "  @-Error Extension\n", 20);
	write(STDERR_FILENO, "*/\n", 3);
	exit(EXIT_FAILURE);
}

void	allocation_error(void)
{
	write(2, "Error : allocation error occured\n", 33);
}

void	error(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
