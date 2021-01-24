#include "./../include/ft_ssl.h"

void        hub(t_data *data)
{
    if (ft_strcmp(data->type, (uint8_t*)"md5") == 0)
    {
        ft_md5(data);
    }
    else
    {
        puts("Error");
    }
}