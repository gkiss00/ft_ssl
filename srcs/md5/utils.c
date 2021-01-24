#include "./../include/ft_ssl.h"

void        init_md5(t_md5 *tmp)
{
    tmp->h0 = 0x67452301;
    tmp->h1 = 0xEFCDAB89;
    tmp->h2 = 0x98BADCFE;
    tmp->h3 = 0x10325476;
    tmp->a = 0;
    tmp->b = 0;
    tmp->c = 0;
    tmp->d = 0;
    fill_r(tmp);
    fill_k(tmp);
}

uint32_t    get_new_len(uint8_t *msg)
{
    uint32_t    len;
    uint32_t    new_len;

    len = ft_strlen(msg);
    new_len = len + 1;
    if (new_len % 64 <= 56)
        new_len = new_len + (64 - (new_len % 64));
    else
        new_len = new_len + (64 + (new_len % 64));
    return (new_len);
}

uint8_t     *get_new_msg(uint8_t *msg)
{
    uint8_t     *new_msg;
    uint32_t    len;
    uint32_t    new_len;
    uint32_t    i;

    i = 0;
    new_msg = NULL;
    len = ft_strlen(msg);
    new_len = len + 1;
    if (new_len % 64 <= 56)
        new_len = new_len + (64 - (new_len % 64));
    else
        new_len = new_len + (64 + (new_len % 64));
    new_msg = malloc(new_len);
    while(msg[i]){
        new_msg[i] = msg[i];
        ++i;
    }
    new_msg[i] = 128;
    ++i;
    while(i < new_len - 8){
        new_msg[i] = '\0';
        ++i;
    }
    memcpy(new_msg + i, &len, 4);
    i += 4;
    while(i < new_len){
        new_msg[i] = '\0';
        ++i;
    }
    return (new_msg);
}