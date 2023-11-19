#include "../HEADER/Parsing.h"

void    display_error(char *error)
{
    write(STDERR_FILENO, error, ft_strlen(error));
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_FAILURE);
}