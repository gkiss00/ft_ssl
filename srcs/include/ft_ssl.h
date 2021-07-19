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
# include <stdbool.h>
# include <ctype.h>

#define STRING 1
#define FILE 2
#define NB_COMMAND 2

typedef struct          s_option
{
    uint32_t             p;
    uint32_t             q;
    uint32_t             r;
    uint32_t             s;
}                       t_option;

typedef struct          s_node
{
    uint32_t             type;
    uint8_t              *arg;
    uint8_t              *file_name;
    struct s_node         *next;
}                       t_node;

typedef struct		    s_data
{
	uint8_t             *cmd;
    uint8_t             *uppercase_cmd;
    uint8_t             *input;
    struct s_node       *node;
    struct s_option     *opts;
}                       t_data;

typedef struct          s_command
{
    uint8_t              *name;
    void                (*hash)(t_data *data);
    uint32_t            nb_bytes;
    struct s_command    *next;
}                       t_command;

//PROGRAM
void        begin(t_data *data);
void        hub(t_data *data);
void        end(t_data *data);

//MD5
void        ft_md5(t_data *data);
void        hash_md5(uint8_t *msg, uint8_t *hashed);

//SHA256
void        ft_sha256(t_data *data);
void        hash_sha256(uint8_t *msg, uint8_t *hashed);

uint8_t *encrypt_base64(uint8_t *msg);
uint8_t *decrypt_base64(uint8_t *msg);

//ERROR
void     check_error(int argc, char **argv);

uint32_t    ft_strlen(uint8_t *str);
uint32_t    ft_strcmp(uint8_t *s1, uint8_t *s2);
uint8_t     *ft_strdup(uint8_t *s1);
uint8_t     *ft_strjoin(uint8_t *s1, uint8_t *s2);

char        *to_upper(char * temp);

uint8_t		**add_to_tab(uint8_t **tab, uint8_t *str);

//PARSING
void parsing(t_data *data, uint8_t **argv);

//BIT OPERAND
uint64_t small_to_big_endian_64(uint64_t n);
uint32_t big_to_small_endian_32(uint32_t n);
uint32_t left_rotate_32(uint32_t value, unsigned int count);
uint32_t right_rotate_32(uint32_t value, unsigned int count);

//NODE
t_node *new_node(uint32_t type, uint8_t *arg, uint8_t *file_name);
t_node *node_last(t_node *node);
void node_add_back(t_node **head, t_node *new);

t_command *new_command(uint8_t *name, void (*hash)(t_data*));
t_command *command_last(t_command *command);
void command_add_back(t_command **head, t_command *new);



#endif