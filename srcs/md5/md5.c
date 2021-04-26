#include "./../include/ft_ssl.h"

void        ft_md5(t_data *data)
{
    uint32_t    i;
    uint8_t     hashed[16];

    i = 0;
    while(i < ft_tablen(data->args))
    {
        if(data->contents[i] == NULL)
        {

        }
        else
        {
            hash_md5(data->contents[i], hashed);
        }
        ++i;
    }
}