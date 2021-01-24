#include "./../include/ft_ssl.h"

uint32_t    ft_tablen(uint8_t **tab)
{
    uint32_t i;

    i = 0;
    while (tab && tab[i])
        ++i;
    return (i);
}

void        ft_puttab(uint8_t **tab)
{
    uint32_t i;

    i = 0;
    while (tab && tab[i])
    {
        ft_putstrendl_fd(tab[i], 1);
        ++i;
    }
}

void        free_tab(uint8_t **tab)
{
    uint32_t i;

    i = 0;
    while (tab && tab[i])
    {
        free(tab[i]);
        ++i;
    }
    if (tab)
        free(tab);
}