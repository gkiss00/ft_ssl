#include "./../include/ft_ssl.h"

void    check_error_base64(int argc, char **argv) {
    int i = 0;
    int ret = 0;
    char    *input = NULL;
    char    *output = NULL;

    while((ret = getopt(argc - 1, &argv[1], "edi:o:")) != -1) {
        switch(ret){
            case 'e':
                break;
            case 'd':
                break;
            case 'i':
                input = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            case '?':
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }
    for (i = optind; i < argc; i++)
        printf ("Non-option argument %s\n", argv[i]);
    printf("no error: %s %s\n", input, output);
}