#include "./../include/ft_ssl.h"

static void addArg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
}

void    parsing_digest(int argc, char **argv, t_data *data) {
    int i = 0;
    int ret = 0;
    char    *str = NULL;

    while((ret = getopt(argc - 1, &argv[1], "qrps:")) != -1) {
        switch(ret){
            case 'q':
                data->opts_digest->q = 1;
                break;
            case 'r':
                data->opts_digest->r = 1;
                break;
            case 'p':
                data->opts_digest->p = 1;
                break;
            case 's':
                data->opts_digest->s = 1;
                str = optarg;
                addArg(data, STRING, (uint8_t *)str, NULL);
                break;
            case '?':
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }
    for (i = optind + 1; i < argc; i++){
        addArg(data, STRING, NULL, (uint8_t *)argv[i]);
    }
}