#include "./../include/ft_ssl.h"

void        ft_sha256(t_data *data)
{
    uint32_t    i;
    uint8_t     hashed[32];

    i = 0;
    while(i < ft_tablen(data->args))
    {
        if(data->contents[i] == NULL)
        {

        }
        else
        {
            hash_sha256(data->contents[i], hashed);
        }
        ++i;
    }
}