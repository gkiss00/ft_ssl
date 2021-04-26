#include "./../include/ft_ssl.h"

static int  get_options(t_data *data, int argc, char **argv, int i)
{
    int     j;
    int     len;

    while(i < argc)
    {
        len = ft_strlen((uint8_t*)argv[i]);
        if (len != 0 && argv[i][0] == '-')
        {
            j = 0;
            while(++j < len)
            {
                if (argv[i][j] == 'p')
                    data->opts->p = 1;
                if (argv[i][j] == 'q')
                    data->opts->q = 1;
                if (argv[i][j] == 'r')
                    data->opts->r = 1;
                if (argv[i][j] == 's')
                    data->opts->s = 1;
            }
            ++i;
        }
        else
            break ;
    }
    return (i);
}

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
    data->msg = in;
}

static void fill_data(t_data *data, int argc, char **argv)
{
    int     i;

    i = 1;
    get_stdin_input(data);
    while(i < argc)
    {
        if (i == 1)
        {
            data->type = ft_strdup((uint8_t*)argv[1]);
            i = get_options(data, argc, argv, ++i);
        }
        if (i < argc)
        {
            data->args = add_to_tab(data->args, (uint8_t*)argv[i]);
        }
        ++i;
    }
}

static void init_data(t_data *input, t_option *options)
{
    input->opts = options;
    input->type = NULL;
    input->msg = NULL;
    input->args = NULL;
    input->contents = NULL;
    input->opts->p = 0;
    input->opts->q = 0;
    input->opts->r = 0;
    input->opts->s = 0;
}

int         main(int argc, char **argv)
{
    t_data      data;
    t_option    options;

    
    init_data(&data, &options);
    if (check_error(argc, argv) == 2)
        return (1);
    fill_data(&data, argc, argv);
    begin(&data);
    end(&data);
    return (0);
}