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
# include <time.h>
# include <math.h>
# include <limits.h>

#define STRING 1
#define FILE 2

#define ECB 1
#define CBC 2

#define ENCRYPT 1
#define DECRYPT 2

#define MALLOC_ERROR "Malloc error, exit"

#define BIT(n, k) (n >> k) & 1
#define CIRCULAR_SHIFT_28(n, k) ((n << k + 4) >> 4) | (n >> (28 - k))

#define PRINT_UINT64(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4]), printf(" "), print_uint8(&((uint8_t *)n)[5]), printf(" "), print_uint8(&((uint8_t *)n)[6]), printf(" "), print_uint8(&((uint8_t *)n)[7])
#define PRINT_UINT56(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4]), printf(" "), print_uint8(&((uint8_t *)n)[5]), printf(" "), print_uint8(&((uint8_t *)n)[6])
#define PRINT_UINT48(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4]), printf(" "), print_uint8(&((uint8_t *)n)[5]), printf(" ")
#define PRINT_UINT40(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3]), printf(" "), print_uint8(&((uint8_t *)n)[4])
#define PRINT_UINT32(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2]), printf(" "), print_uint8(&((uint8_t *)n)[3])
#define PRINT_UINT24(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1]), printf(" "), print_uint8(&((uint8_t *)n)[2])
#define PRINT_UINT16(n) print_uint8(&((uint8_t *)n)[0]), printf(" "), print_uint8(&((uint8_t *)n)[1])
#define PRINT_UINT8(n) print_uint8(&((uint8_t *)n)[0])

#define X(n) (n >> 1) & 15
#define Y(n) (n & 33) == 0 ? 0 : (n & 33) == 1 ? 1 : (n & 33) == 32 ? 2 : 3

#define XOR(n, k) (n ^ k)

typedef struct              s_bin
{
    uint8_t                *binary;
    uint32_t                size;
}                           t_bin;

typedef struct              s_option_digest
{
    uint32_t                p; // stdin
    uint32_t                q; // quiet
    uint32_t                r; // reverse
    uint32_t                s; // string
}                           t_option_digest;

typedef struct              s_option_base64
{
    uint32_t                d; // decrypt
    uint32_t                e; // encrypt (default)
}                           t_option_base64;

typedef struct              s_option_cipher
{
    uint32_t                a; // decrypt/encrypt
    int                     mode; // ENCRYPT DECRYPT
    uint8_t                 *vector; // vector hexadecimal
    uint8_t                 *salt; // salt hexadecimal
    uint8_t                 *password; // password
    uint8_t                 *key; // key hexadecimal
    int                     kind; // ECB CBC 
}                           t_option_cipher;

typedef struct              s_node
{
    uint32_t                type;
    uint8_t                 *arg;
    uint8_t                 *file_name;
    uint32_t                file_size;
    struct s_node           *next;
}                           t_node;

typedef struct		        s_data
{
	uint8_t                 *cmd;
    uint8_t                 *uppercase_cmd;
    uint8_t                 *input;
    uint32_t                input_size;
    uint8_t                 *output_file;
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
void        hub(int argc, char **argv, t_data *data);

// MD5
void        ft_md5(int argc, char **argv, t_data *data);
void        hash_md5(uint8_t *msg, uint8_t *hashed, uint32_t size);

// SHA256
void        ft_sha256(int argc, char **argv, t_data *data);
void        hash_sha256(uint8_t *msg, uint8_t *hashed, uint32_t size);

// BASE64
void        ft_base64(int argc, char **argv, t_data *data);
uint8_t     *encrypt_base64(uint8_t *msg, uint32_t size);
uint8_t     *decrypt_base64(uint8_t *msg);

// DES
void        ft_des(int argc, char **argv, t_data *data);
void        pre_process(t_data *data);

// GENRSA
void        ft_genrsa(int argc, char **argv, t_data *data);

// ERROR
void        check_error(int argc);
void        check_error_base64(int argc, char **argv);
void        print_usage_error(char **argv);

// UTILS
void        exit_error(char *error);
uint32_t    ft_strlen(uint8_t *str);
uint32_t    ft_strcmp(uint8_t *s1, uint8_t *s2);
uint8_t     *ft_strdup(uint8_t *s1);
uint8_t     *ft_strjoin(uint8_t *s1, uint8_t *s2);
uint8_t     *first_line(uint8_t *temp);
char        *to_upper(char * temp);
uint8_t		**add_to_tab(uint8_t **tab, uint8_t *str);
uint8_t     *str_to_hex(uint8_t str[16]);
void        print_uint8(uint8_t *n);
void        fill_data_binary_contents(t_data *data);
uint8_t     *ft_strjoin_2(uint8_t *s1, uint8_t *s2, int size1, int size2);
void        redirect(uint8_t *path);

// PARSING
void        get_stdin_binary_input(t_data *data);
void        add_arg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name);
void        parsing_digest(int argc, char **argv, t_data *data);
void        parsing_base64(int argc, char **argv, t_data *data);
void        parsing_cipher(int argc, char **argv, t_data *data);
void        parsing_genrsa(int argc, char **argv, t_data *data);

// BIT OPERAND
uint64_t    small_to_big_endian_64(uint64_t n);
uint32_t    big_to_small_endian_32(uint32_t n);
uint32_t    left_rotate_32(uint32_t value, unsigned int count);
uint32_t    right_rotate_32(uint32_t value, unsigned int count);

// BIN
t_bin       *new_bin(uint8_t *binary, uint32_t size);

// NODE
t_node      *new_node(uint32_t type, uint8_t *arg, uint8_t *file_name);
t_node      *node_last(t_node *node);
void        node_add_back(t_node **head, t_node *new);

// COMMAND
t_command   *new_command(uint8_t *name, void (*hash)(int, char**, t_data*));
t_command   *command_last(t_command *command);
void        command_add_back(t_command **head, t_command *new);



#endif