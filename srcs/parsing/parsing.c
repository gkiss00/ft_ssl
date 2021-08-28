#include "./../include/ft_ssl.h"

void add_arg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
}

void  get_stdin_binary_input(t_data *data)
{
    int         ret;
    int         size = 0;
    uint8_t     buf[10];
    uint8_t     *content;

    ret = 0;
    content = NULL;
    while((ret = read(0, buf, 9)) > 0)
    {
        buf[ret] = '\0';
        content = ft_strjoin_2(content, buf, size, ret);
        size += ret;
    }
    if(content == NULL)
        content = (uint8_t*)ft_strdup((uint8_t*)"");
    data->input = content;
    data->input_size = size;
}