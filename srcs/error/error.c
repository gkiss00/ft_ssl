#include "./../include/ft_ssl.h"

static void print_usage() {
    printf("Standard commands:\n");
    printf("Message Digest commands:\n");
    printf("\t- md5\n");
    printf("\t- sha256\n");
    printf("Cipher commands:\n");
    printf("\t- base64\n");
    printf("\t- des\n");
    printf("\t- des-ecb\n");
    printf("\t- des-cbc\n");
    exit(EXIT_FAILURE);
}

void print_usage_error(char **argv)
{
    printf("ft_ssl: Error: %s is an invalid command\n", argv[1]);
    print_usage();
}

void     check_error(int argc)
{
    if (argc == 1)
        print_usage();
}