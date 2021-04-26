#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <assert.h> 

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

void        begin(t_data *data);
void        hub(t_data *data);
void        end(t_data *data);

void        ft_md5(t_data *data);
void        hash_md5(uint8_t *msg, uint8_t *hashed);

void        ft_sha256(t_data *data);
void        hash_sha256(uint8_t *msg, uint8_t *hashed);

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

uint64_t small_to_big_endian_64(uint64_t n);
uint32_t big_to_small_endian_32(uint32_t n);
uint32_t left_rotate_32(uint32_t value, unsigned int count);
uint32_t right_rotate_32(uint32_t value, unsigned int count);



#endif