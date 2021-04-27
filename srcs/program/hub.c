#include "./../include/ft_ssl.h"

void        hub(t_data *data)
{
    if (ft_strcmp(data->cmd, (uint8_t*)"md5") == 0) {
        ft_md5(data);
    } else if (ft_strcmp(data->cmd, (uint8_t*)"sha256") == 0) {
        ft_sha256(data);
    }
}