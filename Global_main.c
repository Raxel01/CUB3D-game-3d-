#include "./HEADER/Parsing.h"


int main (int ac, char **av)
{
    int fd;

    if (ac == 1 || ac > 2)
        display_error("@-PLEASE ENTER ENOUGH ARGUMENTS");
    fd = open(av[1], O_RDONLY, 0777);
    if (fd == -1)
        display_error(strerror(errno));
    char *newline = ft_strtrim("     |NO LOL  ./path_to_lol|      ");
    printf("%s\n", newline);
    free(newline);
    // execution(parsing(fd));
    return (0);
}
