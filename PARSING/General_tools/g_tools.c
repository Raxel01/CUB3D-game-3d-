#include "../../HEADER/Parsing.h"

int ft_strlen(char *data)
{
    int i;

    i = 0;
    if (!data)
        return (0);
    while (data[i])
        i++;
    return (i);
}

int getstart(char *data)
{
    int start;

    start = 0;
    while (data[start] && (data[start] == ' ' || data[start] == '\t'))
        start++;
    return (start);
}

int getend(char *data)
{
    int end;

    end = ft_strlen(data) - 1;
    while (end >= 0 && (data[end] == ' ' || data[end] == '\t'))
        end--;
    return (end);
}

char    *ft_strtrim(char *to_trim)
{
    t_trim elem;
   

    elem.i = 0;
    elem.start_trim = getstart(to_trim);
    elem.end_trim = getend(to_trim);
    elem.trim_len = elem.end_trim - elem.start_trim;
    elem.trimmed = malloc(sizeof(char )* (elem.trim_len + 2));
    if (!elem.trimmed)
        return (NULL);
    while (to_trim[elem.start_trim] && elem.start_trim <= elem.end_trim)
    {
        elem.trimmed[elem.i] = to_trim[elem.start_trim];
        elem.i++;
        elem.start_trim++;
    }
    elem.trimmed[elem.i] = '\0';
    return(elem.trimmed);
}