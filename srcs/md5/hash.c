#include "./../include/ft_ssl.h"

static uint32_t         leftrotate(int x, int y)
{
    return ((x << y) | (x >> (32 - y)));
}

static void set_f_g(t_md5 *md5, uint32_t *f, uint32_t *g, int i)
{
    if (i < 16)
    {
        *f = ((md5->b & md5->c) | (~md5->b & md5->d));
        *g = i;
    }
    else if (i < 32)
    {
        *f = ((md5->d & md5->b) | (~md5->d & md5->c));
        *g = ((5 * i) + 1) % 16;
    }
    else if (i < 48)
    {
        *f = md5->b ^ md5->c ^ md5->d;
        *g = ((3 * i) + 5) % 16;
    }
    else
    {
        *f = md5->c ^ (md5->b | ~md5->d);
        *g = (7 * i) % 16;
    }
}

static void bcl2(t_md5 *md5, uint32_t *w)
{
    uint32_t    i;
    uint32_t    tmp;
    uint32_t    f;
    uint32_t    g;

    i = -1;
    while(++i < 64)
    {
        set_f_g(md5, &f, &g, i);
        tmp = md5->d;
        md5->d = md5->c;
        md5->c = md5->b;
        md5->b = leftrotate(md5->a + f + md5->k[i] + w[g], md5->r[i]) + md5->b;
        md5->a = tmp;
    }
}

static void     get_hashed(t_md5 *md5, uint8_t *new_msg, uint8_t *msg)
{
    uint32_t    i;
    uint32_t *w;

    i = 0;
    while(i < get_new_len(msg) / 64)
    {
        w = (uint32_t *) (new_msg + (i * 64));
        md5->a = md5->h0;
        md5->b = md5->h1;
        md5->c = md5->h2;
        md5->d = md5->h3;
        bcl2(md5, w);
        md5->h0 = md5->h0 + md5->a;
        md5->h1 = md5->h1 + md5->b;
        md5->h2 = md5->h2 + md5->c;
        md5->h3 = md5->h3 + md5->d;
        ++i;
    }
}

uint8_t     *hash(uint8_t *msg)
{
    uint8_t *hashed;
    uint8_t *new_msg;
    t_md5   md5;

    init_md5(&md5);
    new_msg = get_new_msg(msg);
    get_hashed(&md5, new_msg, msg);

    uint8_t *p;
 
    // display result
 
    p=(uint8_t *)&md5.h0;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
 
    p=(uint8_t *)&md5.h1;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
 
    p=(uint8_t *)&md5.h2;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
 
    p=(uint8_t *)&md5.h3;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    puts("");
    hashed = NULL;
    return (hashed);
}