/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 02:55:14 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/18 15:49:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

typedef struct trim
{
    int     start_trim;
    int     end_trim;
    int     trim_len;
    char    *trimmed;
    int     i;
}   t_trim;

/*
    @- error phase :
*/
void    display_error(char *error);

/*
    @-General function:
*/
int     ft_strlen(char *data);
char    *ft_strtrim(char *to_trim);
int     getend(char *data);
int     getstart(char *data);

#endif