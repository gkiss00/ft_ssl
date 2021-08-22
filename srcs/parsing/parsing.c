#include "./../include/ft_ssl.h"

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