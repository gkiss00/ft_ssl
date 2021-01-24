#include "./../include/ft_ssl.h"

void        end(t_data *data)
{
    int     i;

    i = 0;
    free(data->type);
    free(data->msg);
    while(data->args[i])
    {
        free(data->args[i]);
        free(data->contents[i]);
        ++i;
    }
    free(data->args);
    free(data->contents);
}