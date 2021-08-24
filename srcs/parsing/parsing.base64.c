#include "./../include/ft_ssl.h"

static void print_usage() {
    printf("base64: usage:\n");
    printf("\t-d decrypt\n");
    printf("\t-e encrypt\n");
    printf("\t-i <file> input\n");
    printf("\t-o <file> output\n");
}

static void addArg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
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
                addArg(data, FILE, NULL, (uint8_t*)optarg);
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
        addArg(data, FILE, NULL, (uint8_t*)argv[i]);
        break;
    }
}