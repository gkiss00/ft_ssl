#include "./../include/ft_ssl.h"

static void print_usage() {
    printf("genrsa: usage:\n");
    printf("\t-o <file> output_file\n");
}

void    parsing_genrsa(int argc, char **argv, t_data *data) {
    int ret = 0;

    while((ret = getopt(argc - 1, &argv[1], "o:")) != -1) {
        switch(ret){
            case 'o':
                data->output_file = ft_strdup((uint8_t*)optarg);
                break;
            case '?':
                print_usage();
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }
}