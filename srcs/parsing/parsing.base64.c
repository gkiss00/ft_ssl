#include "./../include/ft_ssl.h"

static void print_usage() {
    printf("base64: usage:\n");
    printf("\t-d decrypt\n");
    printf("\t-e encrypt\n");
    printf("\t-i <file> input\n");
    printf("\t-o <file> output\n");
}

void    parsing_base64(int argc, char **argv, t_data *data) {
    int i = 0;
    int ret = 0;

    while((ret = getopt(argc - 1, &argv[1], "edi:o:")) != -1) {
        switch(ret){
            case 'e':
                data->opts_base64->e = 1;
                break;
            case 'd':
                data->opts_base64->d = 1;
                break;
            case 'i':
                add_arg(data, FILE, NULL, (uint8_t*)optarg);
                break;
            case 'o':
                data->output_file = (uint8_t*)optarg;
                break;
            case '?':
                print_usage();
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }
    for (i = optind + 1; i < argc; i++){
        add_arg(data, FILE, NULL, (uint8_t*)argv[i]);
        break;
    }
    if (data->node == NULL)
        get_stdin_binary_input(data);
}