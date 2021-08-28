#include "./../include/ft_ssl.h"

static void check_stream(uint8_t *msg) {
    for (uint32_t i = 0; i < ft_strlen(msg); ++i) {
        if(strchr("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789+/", msg[i]) == NULL && msg[i] != '='){
            fprintf(stderr, "Invalid character in input stream.");
            exit(EXIT_FAILURE);
        }
    }
}

static void ft_decrypt(t_data *data) {
    uint8_t *code = NULL;

    if(data->node == NULL) {
        check_stream(first_line(data->input));
        code = decrypt_base64(first_line(data->input));
    } else {
        if(data->node->arg == NULL){
            fprintf(stderr, "Unable to open '%s': No such file or directory", data->node->file_name);
        } else {
            check_stream(first_line(data->node->arg));
            code = decrypt_base64(first_line(data->node->arg));
        }
    }
    redirect(data->output_file);
    printf("%s", (char*)code);
}

static void ft_encrypt(t_data *data) {
    uint8_t *code = NULL;

    if(data->node == NULL) {
        code = encrypt_base64(data->input, data->input_size);
    } else {
        if(data->node->arg == NULL){
            fprintf(stderr, "Unable to open '%s': No such file or directory", data->node->file_name);
        } else {
            code = encrypt_base64(data->node->arg, data->node->file_size);
        }
    }
    redirect(data->output_file);
    printf("%s\n", (char*)code);
}

void        ft_base64(int argc, char **argv, t_data *data) {
    parsing_base64(argc, argv, data);
    fill_data_binary_contents(data);

    if(data->opts_base64->d == 1) {
        // Decrypt mode
        ft_decrypt(data);
    } else {
        // Encrypt mode
        ft_encrypt(data);
    }
}