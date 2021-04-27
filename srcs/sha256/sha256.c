#include "./../include/ft_ssl.h"

static void output_error(t_data *data, t_node *node) {
    printf("%s: %s: No such file or directory\n", data->cmd, node->file_name);
}

static void output_hash(uint8_t *hashed, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        printf("%02x", hashed[i]);
    }
}

static void output_normal(t_data *data, uint8_t *hashed, t_node *node) {
    if (data->opts->q == 1) {
        output_hash(hashed, 32);    
    } else {
        if (data->opts->r == 0) {
            if(node->type == STRING) {
                printf("%s (\"%s\") = ", data->uppercase_cmd, node->arg);
            } else if (node->type == FILE) {
                printf("%s (%s) = ", data->uppercase_cmd, node->file_name);
            }
            output_hash(hashed, 32);
            
        } else {
            output_hash(hashed, 32);
            if(node->type == STRING) {
                printf(" \"%s\"", node->arg);
            } else if (node->type == FILE) {
                printf(" %s", node->file_name);
            }
        }
    }
    printf("\n");
}

static void output(t_data *data, uint8_t *hashed, t_node *node) {
    if(node->arg == NULL) {
        output_error(data, node);
    } else {
        output_normal(data, hashed, node);
    }
}

static void output_input(t_data *data) {
    uint8_t     hashed[32];
    if(data->input) {
        if (data->opts->p) {
            printf("%s", data->input);
        }
        hash_sha256(data->input, hashed);
        output_hash(hashed, 32);
        printf("\n");
    }
}

void        ft_sha256(t_data *data)
{
    uint8_t     hashed[32];

    t_node *tmp = data->node;
    output_input(data);
    while(tmp) {
        if(tmp->arg)
            hash_sha256(tmp->arg, hashed);
        output(data, hashed, tmp);
        tmp = tmp->next;
    }
}