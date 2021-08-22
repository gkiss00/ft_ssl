#include "./../include/ft_ssl.h"

static void print_option_error(char **argv, char opt) {
    printf("%s: illegal option -- %c\n", argv[1], opt);
    printf("usage: md5 [-pqr] [-s string] [files ...]\n");
    exit(EXIT_FAILURE);
}

static void print_string_error(char **argv) {
    printf("%s: option requires an argument -- s\n", argv[1]);
    printf("usage: md5 [-pqr] [-s string] [files ...]\n");
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

void     check_error_digest(char **argv)
{
    check_args(argv);
}