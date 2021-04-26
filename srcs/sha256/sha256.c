#include "./../include/ft_ssl.h"

void        ft_sha256(t_data *data)
{
    uint32_t    i;
    uint8_t     *hashed;

    i = 0;
    while(i < ft_tablen(data->args))
    {
        if(data->contents[i] == NULL)
        {

        }
        else
        {
            hashed = hash_sha256(data->contents[i]);
        }
        ++i;
    }
}