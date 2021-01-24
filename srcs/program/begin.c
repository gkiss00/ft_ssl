#include "./../include/ft_ssl.h"

static uint8_t  *get_content(int fd)
{
    int     ret;
    uint8_t    buf[10];
    uint8_t    *content;

    ret = 0;
    content = NULL;
    while((ret = read(fd, buf, 9)) > 0)
    {
        buf[ret] = '\0';
        content = ft_strjoin(content, buf);
    }
    return (content);
}

static uint8_t *get_fd_content(uint8_t *path)
{
    int     fd;

    fd = open((char*)path, O_RDONLY);
    if (fd == -1)
        return (NULL);
    return (get_content(fd));
}

static void        fill_data_contents(t_data *data)
{
    uint32_t    i;
    uint8_t     *content;

    i = 0;
    data->contents = malloc(ft_tablen(data->args) + 1);
    while(data->args && data->args[i])
    {
        content = get_fd_content(data->args[i]);
        data->contents = add_to_tab(data->contents, content);
        ++i;
    }
    data->contents[i] = NULL;
}

void        begin(t_data *data)
{
    fill_data_contents(data);
    hub(data);
}