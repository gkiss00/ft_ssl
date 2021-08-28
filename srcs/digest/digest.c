#include "./../include/ft_ssl.h"

static void output_error(t_data *data, t_node *node) {
    printf("%s: %s: No such file or directory\n", data->cmd, node->file_name);
}

static void output_hash(uint8_t *hashed, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        printf("%02x", hashed[i]);
    }
}

static void output_normal(t_data *data, uint8_t *hashed, t_node *node, int size) {
    if (data->opts_digest->q == 1) {
        output_hash(hashed, size);    
    } else {
        if (data->opts_digest->r == 0) {
            if(node->type == STRING) {
                printf("%s (\"%s\") = ", data->uppercase_cmd, node->arg);
            } else if (node->type == FILE) {
                printf("%s (%s) = ", data->uppercase_cmd, node->file_name);
            }
            output_hash(hashed, size);
            
        } else {
            output_hash(hashed, size);
            if(node->type == STRING) {
                printf(" \"%s\"", node->arg);
            } else if (node->type == FILE) {
                printf(" %s", node->file_name);
            }
        }
    }
    printf("\n");
}

static void output(t_data *data, uint8_t *hashed, t_node *node, int size) {
    if(node->arg == NULL) {
        output_error(data, node);
    } else {
        output_normal(data, hashed, node, size);
    }
}

static void output_input(t_data *data, int size, void (*hash)(uint8_t *, uint8_t *)) {
    uint8_t     hashed[size];
    if(data->input) {
        if (data->opts_digest->p) {
            printf("%s", data->input);
        }
        hash(data->input, hashed);
        output_hash(hashed, size);
        printf("\n");
    }
}

static void        ft_digest(int argc, char **argv, t_data *data, int size, void (*hash)(uint8_t *, uint8_t *))
{
    uint8_t     hashed[size];
    t_node *tmp;

    parsing_digest(argc, argv, data);
    if (data->opts_digest->p == 1 || data->node == NULL)
        get_stdin_input(data);
    fill_data_binary_contents(data);
    tmp = data->node;
    output_input(data, size, hash);
    while(tmp) {
        if(tmp->arg)
            hash(tmp->arg, hashed);
        output(data, hashed, tmp, size);
        tmp = tmp->next;
    }
}

void        ft_sha256(int argc, char **argv, t_data *data) {
    ft_digest(argc, argv, data, 32, &hash_sha256);
}

void        ft_md5(int argc, char **argv, t_data *data) {
    ft_digest(argc, argv, data, 16, &hash_md5);
}