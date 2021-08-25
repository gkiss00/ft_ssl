#include "./../include/ft_ssl.h"

static void print_usage() {
    printf("des des-ecb des-cbc: usage:\n");
    printf("\t-a encrypt/decrypt\n");
    printf("\t-d decrypt\n");
    printf("\t-e encrypt\n");
    printf("\t-i <file> input\n");
    printf("\t-o <file> output\n");
    printf("\t-v <hex> vector\n");
    printf("\t-s <hex> salt\n");
    printf("\t-p <str> password\n");
    printf("\t-k <hex> key\n");
}

static void addArg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
}

static uint8_t *generate_salt(){
    uint8_t *salt;
    long int r = random();
    salt = calloc(8, 1);
    memcpy(salt, &r, 4);
    r = random();
    memcpy(&salt[4], &r, 4);
    return salt;
}

static uint8_t *generate_key(uint8_t *pwd, uint8_t salt[8]){
    while(ft_strlen(pwd) < 8 && ft_strlen(pwd) % 8 != 0) {
        uint8_t *tmp = calloc((ft_strlen(pwd) * 2) + 1, 1);
        memcpy(tmp, pwd, ft_strlen(pwd));
        memcpy(&tmp[ft_strlen(pwd)], pwd, ft_strlen(pwd));
        free(pwd);
        pwd = tmp;
    }
    int size = ft_strlen(pwd) / 8;
    uint8_t res[8];
    memcpy(res, pwd, 8);
    for (int i = 1; i < size; ++i) {
        uint8_t tmp[8];
        memcpy(tmp, &pwd[i * 8], 8);
        for (int k = 0; k < 8; ++k){
            res[k] ^= tmp[k];
        }
    }
    for (int k = 0; k < 8; ++k){
        res[k] ^= salt[k];
    }
    free(pwd);
    return ft_strdup(res);
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
            fprintf(stderr, "Verify failure\nbad password read\n");
            exit(EXIT_FAILURE);
        }
    }

    // salt
    if(data->opts_cipher->salt == NULL) {
        // generate randomly
        data->opts_cipher->salt = generate_salt();
    } else {
        uint8_t *tmp = calloc(16, 1);

        if((int)ft_strlen(data->opts_cipher->salt) < 16)
            fprintf(stderr, "hex string is too short, padding with zero bytes to length\n");
        if(ft_strlen(data->opts_cipher->salt) > 16)
            fprintf(stderr, "hex string is too long, ignoring excess\n");
        memset(tmp, '0', 16);
        memcpy(tmp, data->opts_cipher->salt, ft_strlen(data->opts_cipher->salt) > 16 ? 16 : ft_strlen(data->opts_cipher->salt));
        uint8_t *hex = str_to_hex(tmp);
        free(tmp);
        free(data->opts_cipher->salt);
        data->opts_cipher->salt = hex;
        if(hex == NULL){
            fprintf(stderr, "non-hex digit\ninvalid hex salt value\n");
            exit(EXIT_FAILURE);
        }
    }

    // key
    if(data->opts_cipher->key == NULL) {
        //generate from pass and salt
        data->opts_cipher->key = generate_key(ft_strdup(data->opts_cipher->password), data->opts_cipher->salt);
    } else {
        uint8_t *tmp = calloc(16, 1);

        if((int)ft_strlen(data->opts_cipher->key) < 16)
            fprintf(stderr, "hex string is too short, padding with zero bytes to length\n");
        if((int)ft_strlen(data->opts_cipher->key) > 16)
            fprintf(stderr, "hex string is too long, ignoring excess\n");
        memset(tmp, '0', 16);
        memcpy(tmp, data->opts_cipher->key, ft_strlen(data->opts_cipher->key) > 16 ? 16 : ft_strlen(data->opts_cipher->key));
        uint8_t *hex = str_to_hex(tmp);
        free(tmp);
        free(data->opts_cipher->key);
        data->opts_cipher->key = hex;
        if(hex == NULL){
            fprintf(stderr, "non-hex digit\ninvalid hex key value\n");
            exit(EXIT_FAILURE);
        }
    }

    // vector
    if(data->opts_cipher->vector == NULL) {
        //generate from pass and salt
    } else {
        uint8_t *tmp = calloc(16, 1);

        if((int)ft_strlen(data->opts_cipher->vector) < 16)
            fprintf(stderr, "hex string is too short, padding with zero bytes to length\n");
        if(ft_strlen(data->opts_cipher->vector) > 16)
            fprintf(stderr, "hex string is too long, ignoring excess\n");
        memset(tmp, '0', 16);
        memcpy(tmp, data->opts_cipher->vector, (int)ft_strlen(data->opts_cipher->vector) > 16 ? 16 : ft_strlen(data->opts_cipher->vector));
        uint8_t *hex = str_to_hex(tmp);
        free(tmp);
        free(data->opts_cipher->vector);
        data->opts_cipher->vector = hex;
        if(hex == NULL){
            fprintf(stderr, "non-hex digit\ninvalid hex vector value\n");
            exit(EXIT_FAILURE);
        }
    }
}

void    parsing_cipher(int argc, char **argv, t_data *data) {
    int i = 0;
    int ret = 0;

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
                addArg(data, FILE, NULL, (uint8_t*)optarg);
                break;
            case 'o':
                data->output_file = ft_strdup((uint8_t*)optarg);
                break;
            case 'k':
                data->opts_cipher->key = ft_strdup((uint8_t*)optarg);
                break;
            case 'p':
                data->opts_cipher->password = ft_strdup((uint8_t*)optarg);
                break;
            case 's':
                data->opts_cipher->salt = ft_strdup((uint8_t*)optarg);
                break;
            case 'v':
                data->opts_cipher->vector = ft_strdup((uint8_t*)optarg);
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
        addArg(data, FILE, NULL, (uint8_t *)argv[i]);
    }
    pre_process(data);
}