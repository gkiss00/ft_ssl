#include "./../include/ft_ssl.h"

void add_arg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
}

void get_stdin_input(t_data *data)
{
    uint32_t    ret;
    uint8_t     buf[10];
    uint8_t     *in;

    ret = 0;
    in = NULL;
    while((ret = read(0, buf, 9)) > 0)
    {
        buf[ret] = '\0';
        in = ft_strjoin(in, buf);
    }
    data->input = in;
}