#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct          s_option
{
    uint32_t             p;
    uint32_t             q;
    uint32_t             r;
    uint32_t             s;
}                       t_option;

typedef struct		    s_data
{
	uint8_t             *type;
    uint8_t             *msg;
    uint8_t             **args;
    uint8_t             **contents;
    struct s_option     *opts;
}                       t_data;

typedef struct      s_md5
{
    uint32_t             h0;
    uint32_t             h1;
    uint32_t             h2;
    uint32_t             h3;
    uint32_t             a;
    uint32_t             b;
    uint32_t             c;
    uint32_t             d;
    uint32_t             r[64];
    uint32_t             k[64];
}                   t_md5;

void        begin(t_data *data);
void        hub(t_data *data);
void        end(t_data *data);

void        ft_md5(t_data *data);
uint8_t     *hash(uint8_t *msg);
void        fill_k(t_md5 *tmp);
void        fill_r(t_md5 *tmp);
uint8_t     *get_new_msg(uint8_t *msg);
uint32_t    get_new_len(uint8_t *msg);
void        init_md5(t_md5 *tmp);

int         check_error(int argc, char **argv);

uint32_t    ft_strlen(uint8_t *str);
uint32_t    ft_strcmp(uint8_t *s1, uint8_t *s2);
uint8_t     *ft_strdup(uint8_t *s1);
uint8_t     *ft_strjoin(uint8_t *s1, uint8_t *s2);

void		ft_putchar_fd(uint8_t c, int fd);
void		ft_putstr_fd(uint8_t *str, int fd);
void		ft_putstrendl_fd(uint8_t *str, int fd);

uint32_t    ft_tablen(uint8_t **tab);
void        ft_puttab(uint8_t **tab);
void        free_tab(uint8_t **tab);

uint8_t		**add_to_tab(uint8_t **tab, uint8_t *str);

#endif