#include "./../include/ft_ssl.h"

static void print_error(char **argv)
{
    printf("ft_ssl: Error: %s is an invalid command\n", argv[1]);
    printf("Standard commands:\n");
    printf("Message Digest commands:\n");
    printf("Message Digest commands:\n");
    printf("- md5");
    printf("- sha256\n");
    printf("Cipher commands:");
    exit(EXIT_FAILURE);
}

static void check_type_args(char **argv)
{
    if(strcmp(argv[1], "md5") == 0)
        return ;
    if(strcmp(argv[1], "sha256") == 0)
        return ;
    print_error(argv);
}

static void check_nb_args(int argc)
{
    if (argc == 1)
    {
        printf("No arguments passed to the program\n");
        exit(EXIT_FAILURE);
    }
}

void     check_error(int argc, char **argv)
{
    check_nb_args(argc);
    check_type_args(argv);
}