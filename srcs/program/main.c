#include "./../include/ft_ssl.h"

static void getCmd(t_data *data, uint8_t **argv) {
    data->cmd = (uint8_t*)strdup((char*)argv[1]);
    data->uppercase_cmd = (uint8_t*)to_upper((char*)argv[1]);
}

static void init_data(
    t_data *data, 
    t_option_digest *options_digest, 
    t_option_base64 *options_base64, 
    t_option_cipher *options_cipher
) {
    data->opts_digest = options_digest;
    data->opts_base64 = options_base64;
    data->opts_cipher = options_cipher;

    data->cmd = NULL;
    data->uppercase_cmd = NULL;
    data->input = NULL;
    data->output_file = NULL;
    data->node = NULL;

    data->opts_digest->p = 0;
    data->opts_digest->q = 0;
    data->opts_digest->r = 0;
    data->opts_digest->s = 0;

    data->opts_base64->d = 0;
    data->opts_base64->e = 0;

    data->opts_cipher->a = 0;
    data->opts_cipher->mode = ENCRYPT;
    data->opts_cipher->vector = NULL;
    data->opts_cipher->salt = NULL;
    data->opts_cipher->password = NULL;
    data->opts_cipher->key = NULL;
}

int         main(int argc, char **argv)
{
    t_data      data;
    t_option_digest    options_digest;
    t_option_base64    options_base64;
    t_option_cipher    options_cipher;
    
    init_data(&data, &options_digest, &options_base64, &options_cipher);
    check_error(argc);
    getCmd(&data, (uint8_t**)argv);
    hub(argc, argv, &data);
    exit(EXIT_SUCCESS);
}