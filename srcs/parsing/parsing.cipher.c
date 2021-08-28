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
    printf("\t-k <hex> key\n");
    printf("\t-p <str> password\n");
}

static uint8_t *generate_salt(){
    uint8_t *salt;
    salt = calloc(8, 1);

    long int r = random();
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

static uint8_t *get_hex(uint8_t *input, char *str) {
    if((int)ft_strlen(input) < 16)
        fprintf(stderr, "hex string is too short, padding with zero bytes to length\n");
    if(ft_strlen(input) > 16)
        fprintf(stderr, "hex string is too long, ignoring excess\n");

    uint8_t *tmp = calloc(16, 1);
    memset(tmp, '0', 16);
    memcpy(tmp, input, ft_strlen(input) > 16 ? 16 : ft_strlen(input));

    uint8_t *hex = str_to_hex(tmp);
    free(tmp);
    free(input);

    if(hex == NULL){
        fprintf(stderr, "non-hex digit\ninvalid hex %s value\n", str);
        exit(EXIT_FAILURE);
    }

    return hex;
}

static uint8_t *add_extra_bytes(uint8_t *str, uint32_t size) {
    char *tmp = calloc(size + (8 - (size % 8)) + 1, 1);
    memset(tmp, 0, size + (8 - (size % 8)) + 1);
    memset(tmp, 8 - (size % 8), size + (8 - (size % 8)));
    memcpy(tmp, str, size);
    free(str);
    return (uint8_t*)tmp;
}

void pre_process(t_data *data){
    // fill message
    if(data->opts_cipher->mode == ENCRYPT) {
        if(data->node) {
            if(data->node->arg) {
                data->node->arg = add_extra_bytes(data->node->arg, (uint32_t)data->node->file_size);
            }
        } else {
            if(data->input) {
                uint32_t size = ft_strlen(data->input);
                data->input = add_extra_bytes(data->input, size);
            }
        }
    } else {
        if(data->node) {
            if(data->node->arg) {
                struct stat file_info;
                stat((char*)data->node->file_name, &file_info);
                data->node->file_size = (uint32_t)file_info.st_size;
            }
        }
    }

    // password
    if(data->opts_cipher->password == NULL && data->opts_cipher->key == NULL){
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
        data->opts_cipher->salt = get_hex(data->opts_cipher->salt, "salt");
    }

    // key
    if(data->opts_cipher->key == NULL) {
        //generate from pass and salt
        data->opts_cipher->key = generate_key(ft_strdup(data->opts_cipher->password), data->opts_cipher->salt);
    } else {
        data->opts_cipher->key = get_hex(data->opts_cipher->key, "key");
    }

    // vector
    if(data->opts_cipher->vector == NULL && data->opts_cipher->kind == CBC) {
        fprintf(stderr, "iv need to be initialized\n");
        exit(EXIT_FAILURE);
    } else if (data->opts_cipher->vector == NULL) { } else {
        data->opts_cipher->vector = get_hex(data->opts_cipher->vector, "vector");
    }
}

void    parsing_cipher(int argc, char **argv, t_data *data) {
    int i = 0;
    int ret = 0;

    if( ft_strcmp(data->cmd, (uint8_t*)"des") == 0 ||
        ft_strcmp(data->cmd, (uint8_t*)"des-cbc") == 0)
        data->opts_cipher->kind = CBC;
    else
        data->opts_cipher->kind = ECB;

    while((ret = getopt(argc - 1, &argv[1], "adei:o:k:p:s:v:")) != -1) {
        switch(ret){
            case 'a':
                data->opts_cipher->a = 1;
                break;
            case 'd':
                data->opts_cipher->mode = DECRYPT;
                break;
            case 'e':
                data->opts_cipher->mode = ENCRYPT;
                break;
            case 'i':
                add_arg(data, FILE, NULL, (uint8_t*)optarg);
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
        add_arg(data, FILE, NULL, (uint8_t *)argv[i]);
    }
    if (data->node == NULL)
        get_stdin_binary_input(data);
}