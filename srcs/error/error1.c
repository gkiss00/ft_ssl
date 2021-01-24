#include "./../include/ft_ssl.h"

static int check_nb_args(int argc)
{
    if (argc == 1)
    {
        ft_putstr_fd((uint8_t*)"No arguments passed to the program", 2);
        return (2);
    }
    return (0);
}

int     check_error(int argc, char **argv)
{
    char *tmp = argv[0];
    tmp = NULL;
    if(check_nb_args(argc) == 2)
        return (2);
    return (0);
}