#include "./../include/ft_ssl.h"

static void output(t_data *data, uint8_t *hashed, t_node *node) {
    data->opts->p = 0;
    node->type = 0;
    for (uint32_t i = 0; i < 32; ++i) {
        printf("%02x", hashed[i]);
    }
    printf("\n");
}

void        ft_sha256(t_data *data)
{
    uint8_t     hashed[16];

    t_node *tmp = data->node;
    while(tmp) {
        hash_sha256(tmp->arg, hashed);
        output(data, hashed, tmp);
        tmp = tmp->next;
    }
}