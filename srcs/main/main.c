#include "./../include/ft_ssl.h"

static void get_stdin_input(t_data *data)
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

static void fill_data(t_data *data, char **argv)
{
    parsing(data, (uint8_t **)argv);
    if (data->opts->p == 1 || data->node == NULL)
        get_stdin_input(data);
}

// static void init_command(t_command *commands) {
//     commands[0].name = "md5";
//     commands[0].uppercase_name = "MD5";
//     commands[0].hash = *hash_md5;
//     commands[0].nb_bytes = 16;

//     commands[1].name = "sha256";
//     commands[1].uppercase_name = "SHA256";
//     commands[1].hash = *hash_sha256;
//     commands[1].nb_bytes = 32;
// }

static void init_data(t_data *data, t_option *options)
{
    data->opts = options;
    data->cmd = NULL;
    data->uppercase_cmd = NULL;
    data->input = NULL;
    data->node = NULL;
    data->opts->p = 0;
    data->opts->q = 0;
    data->opts->r = 0;
    data->opts->s = 0;
}

int         main(int argc, char **argv)
{
    t_data      data;
    t_option    options;
    //t_command   commands[NB_COMMAND];
    
    init_data(&data, &options);
    check_error(argc, argv);
    fill_data(&data, argv);
    begin(&data);
    end(&data);
    exit(EXIT_SUCCESS);
}