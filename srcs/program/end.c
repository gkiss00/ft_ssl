#include "./../include/ft_ssl.h"

void        end(t_data *data)
{
    int     i;

    i = 0;
    free(data->cmd);
    free(data->uppercase_cmd);
    free(data->input);
    t_node *tmp = data->node;
    while(tmp)
    {
        t_node *del = tmp;
        free(tmp->arg);
        tmp = tmp->next;
        free(del);
    }
}