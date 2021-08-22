#include "./../include/ft_ssl.h"

static void addArg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
}

void    parsing_cipher(int argc, char **argv, t_data *data) {
    int i = 0;
    int ret = 0;
    char    *str = NULL;

    while((ret = getopt(argc - 1, &argv[1], "adei:o:k:p:s:v:")) != -1) {
        switch(ret){
            case 'a':
                data->opts_cipher->a = 1;
                break;
            case 'd':
                data->opts_cipher->d = 1;
                break;
            case 'e':
                data->opts_cipher->e = 1;
                break;
            case 'i':
                data->opts_cipher->i = 1;
                str = optarg;
                break;
            case 'o':
                data->opts_cipher->o = 1;
                str = optarg;
                break;
            case 'k':
                data->opts_cipher->k = 1;
                str = optarg;
                break;
            case 'p':
                data->opts_cipher->p = 1;
                str = optarg;
                break;
            case 's':
                data->opts_cipher->s = 1;
                str = optarg;
                break;
            case 'v':
                data->opts_cipher->v = 1;
                str = optarg;
                break;
            case '?':
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }
    for (i = optind + 1; i < argc; i++){
        addArg(data, FILE, NULL, (uint8_t *)argv[i]);
    }
}