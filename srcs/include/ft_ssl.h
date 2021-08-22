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

typedef struct              s_option_digest
{
    uint32_t                p;
    uint32_t                q;
    uint32_t                r;
    uint32_t                s;
}                           t_option_digest;

typedef struct              s_option_base64
{
    uint32_t                d;
    uint32_t                e;
    uint32_t                i;
    uint32_t                o;
}                           t_option_base64;

typedef struct              s_option_cipher
{
    uint32_t                a; //decrypt/encrypt
    uint32_t                d; // decrypt mode
    uint32_t                e; // encrypt mode
    uint32_t                i; // input file
    uint32_t                o; // output file
    uint32_t                k; // key hexadecimal
    uint32_t                p; // password
    uint32_t                s; // salt hexadecimal
    uint32_t                v; // vector hexadecimal
}                           t_option_cipher;

typedef struct              s_node
{
    uint32_t                type;
    uint8_t                 *arg;
    uint8_t                 *file_name;
    struct s_node           *next;
}                           t_node;

typedef struct		        s_data
{
	uint8_t                 *cmd;
    uint8_t                 *uppercase_cmd;
    uint8_t                 *input;
    struct s_node           *node;
    struct s_option_digest  *opts_digest;
    struct s_option_base64  *opts_base64;
    struct s_option_cipher  *opts_cipher;
}                           t_data;

typedef struct              s_command
{
    uint8_t                 *name;
    void                    (*hash)(int argc, char **argv, t_data *data);
    uint32_t                nb_bytes;
    struct s_command        *next;
}                           t_command;

// PROGRAM
void        begin(int argc, char **argv, t_data *data);
void        hub(int argc, char **argv, t_data *data);
void        end(t_data *data);

// MD5
void        ft_md5(int argc, char **argv, t_data *data);
void        hash_md5(uint8_t *msg, uint8_t *hashed);

// SHA256
void        ft_sha256(int argc, char **argv, t_data *data);
void        hash_sha256(uint8_t *msg, uint8_t *hashed);

// BASE64
uint8_t *encrypt_base64(uint8_t *msg);
uint8_t *decrypt_base64(uint8_t *msg);

// ERROR
void        check_error(int argc);
void        check_error_digest(char **argv);
void        check_error_base64(int argc, char **argv);
void        print_usage_error(char **argv);

// UTILS
uint32_t    ft_strlen(uint8_t *str);
uint32_t    ft_strcmp(uint8_t *s1, uint8_t *s2);
uint8_t     *ft_strdup(uint8_t *s1);
uint8_t     *ft_strjoin(uint8_t *s1, uint8_t *s2);

char        *to_upper(char * temp);

uint8_t		**add_to_tab(uint8_t **tab, uint8_t *str);

// PARSING
//void    parsing(t_data *data, uint8_t **argv);
void get_stdin_input(t_data *data);
void    parsing_digest(int argc, char **argv, t_data *data);

// BIT OPERAND
uint64_t small_to_big_endian_64(uint64_t n);
uint32_t big_to_small_endian_32(uint32_t n);
uint32_t left_rotate_32(uint32_t value, unsigned int count);
uint32_t right_rotate_32(uint32_t value, unsigned int count);

// NODE
t_node *new_node(uint32_t type, uint8_t *arg, uint8_t *file_name);
t_node *node_last(t_node *node);
void node_add_back(t_node **head, t_node *new);

t_command *new_command(uint8_t *name, void (*hash)(int, char**, t_data*));
t_command *command_last(t_command *command);
void command_add_back(t_command **head, t_command *new);



#endif