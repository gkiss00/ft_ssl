#include "./../include/ft_ssl.h"

static void print_nb_arg_error() {
    printf("No arguments passed to the program\n");
    exit(EXIT_FAILURE);
}

static void print_usage_error(char **argv)
{
    printf("ft_ssl: Error: %s is an invalid command\n", argv[1]);
    printf("Standard commands:\n");
    printf("Message Digest commands:\n");
    printf("Message Digest commands:\n");
    printf("\t- md5\n");
    printf("\t- sha256\n");
    printf("Cipher commands:\n");
    exit(EXIT_FAILURE);
}

static void print_option_error(char **argv, char opt) {
    printf("%s: illegal option -- %c\n", argv[1], opt);
    printf("usage: md5 [-pqrs] [-s string] [files ...]\n");
    exit(EXIT_FAILURE);
}

static void print_string_error(char **argv) {
    printf("%s: option requires an argument -- s\n", argv[1]);
    printf("usage: md5 [-pqrs] [-s string] [files ...]\n");
    exit(EXIT_FAILURE);
}

static bool isOptionString(uint8_t *arg) {
    return (strchr((char*)arg, 's') != NULL);
}

static void isUnknownOption(char **argv, uint8_t *arg) {
    int i = 1;

    while(arg[i]) {
        if (arg[i] != 'q' && arg[i] != 'r' && arg[i] != 'p' && arg[i] != 's')
            print_option_error(argv, arg[i]);
        ++i;
    }
}

static bool isOption(uint8_t *arg) {
    return (arg[0] == '-');
}

static void check_args(char **argv) {
    int i = 2;
    while(argv[i]) {
        if(isOption((uint8_t*)argv[i])) {
            isUnknownOption(argv, (uint8_t*)argv[i]);
            if (isOptionString((uint8_t*)argv[i])) {
                if (argv[i + 1] == NULL){
                    print_string_error(argv);
                }
            }
        }
        ++i;
    }
}

static void check_cmd(char **argv)
{
    if(strcmp(argv[1], "md5") == 0)
        return ;
    if(strcmp(argv[1], "sha256") == 0)
        return ;
    print_usage_error(argv);
}

static void check_nb_args(int argc)
{
    if (argc == 1)
        print_nb_arg_error();
}

void     check_error(int argc, char **argv)
{
    check_nb_args(argc);
    check_cmd(argv);
    check_args(argv);
}