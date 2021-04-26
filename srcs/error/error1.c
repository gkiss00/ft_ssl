#include "./../include/ft_ssl.h"

static int print_error(char **argv)
{
    ft_putstr_fd((uint8_t*)"ft_ssl: Error: ", 2);
    ft_putstr_fd((uint8_t*)argv[1], 2);
    ft_putstrendl_fd((uint8_t*)" is an invalid command", 2);
    ft_putstrendl_fd((uint8_t*)"Standard commands:\n", 2);
    ft_putstrendl_fd((uint8_t*)"Message Digest commands:\n", 2);
    ft_putstrendl_fd((uint8_t*)"- md5", 2);
    ft_putstrendl_fd((uint8_t*)"- sha256\n", 2);
    ft_putstrendl_fd((uint8_t*)"Cipher commands:", 2);
    return (2);
}

static int check_type_args(char **argv)
{
    if(ft_strcmp((uint8_t*)argv[1], (uint8_t*)"md5") == 0)
        return (0);
    if(ft_strcmp((uint8_t*)argv[1], (uint8_t*)"sha256") == 0)
        return (0);
    return (print_error(argv));
}

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
    if(check_nb_args(argc) == 2)
        return (2);
    if(check_type_args(argv) == 2)
        return (2);
    return (0);
}