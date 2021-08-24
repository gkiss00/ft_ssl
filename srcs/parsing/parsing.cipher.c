#include "./../include/ft_ssl.h"

static void addArg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
}

static void pre_process(t_data *data){
    // fill message
    if(data->node) {
        if(data->node->arg) {
            uint32_t size = ft_strlen(data->node->arg);
            if(size % 8 != 0) {
                char *tmp = calloc(size + (8 - (size % 8)), 1);
                memcpy(tmp, data->node->arg, size + (8 - (size % 8)));
                free(data->node->arg);
                data->node->arg = (uint8_t*)tmp;
            }
        }
    }

    // password
    if(data->opts_cipher->password == NULL){
        data->opts_cipher->password = ft_strdup((uint8_t*)getpass("Enter desencryption password:"));
        uint8_t *comfirm = ft_strdup((uint8_t*)getpass("Verifying - enter desencryption password:"));
        if(ft_strcmp(data->opts_cipher->password, comfirm) != 0) {
            printf("Verify failure\nbad password read\n");
            exit(EXIT_FAILURE);
        }
    }

    // salt
    if(data->opts_cipher->salt == NULL) {
        long int r = random();
        data->opts_cipher->salt = calloc(8, 1);
        memcpy(&r, data->opts_cipher->salt, 8);
    } else {
        uint8_t *tmp = calloc(8, 1);
        memcpy(tmp, data->opts_cipher->salt, 8);
        free(data->opts_cipher->salt);
        long int hex = strtol((char*)tmp, NULL, 16);
        memcpy(data->opts_cipher->salt, &hex, 8);
    }

    // key
    if(data->opts_cipher->key == NULL) {
        //generate from pass and salt
    } else {
        uint32_t size = ft_strlen(data->opts_cipher->key);
        uint8_t *tmp = calloc(8, 1);
        if(size < 8) {
            memcpy(tmp, data->opts_cipher->key, size);
        } else if (size > 8) {
            memcpy(tmp, data->opts_cipher->key, 8);
        }
        free(data->opts_cipher->key);
        long int hex = strtol((char*)tmp, NULL, 16);
        memcpy(data->opts_cipher->key, &hex, 8);
    }
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
                addArg(data, FILE, NULL, (uint8_t*)optarg);
                break;
            case 'o':
                data->opts_cipher->o = 1;
                data->output_file = ft_strdup((uint8_t*)optarg);
                break;
            case 'k':
                data->opts_cipher->k = 1;
                data->opts_cipher->key = ft_strdup((uint8_t*)optarg);
                break;
            case 'p':
                data->opts_cipher->p = 1;
                data->opts_cipher->password = ft_strdup((uint8_t*)optarg);
                break;
            case 's':
                data->opts_cipher->s = 1;
                data->opts_cipher->salt = ft_strdup((uint8_t*)optarg);
                break;
            case 'v':
                data->opts_cipher->v = 1;
                data->opts_cipher->vector = ft_strdup((uint8_t*)optarg);
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
    pre_process(data);
}