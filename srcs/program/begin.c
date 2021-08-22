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
    close(fd);
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
    t_node *tmp = data->node;

    while(tmp) {
        if(tmp->type == FILE) {
            tmp->arg = get_fd_content(tmp->file_name);
        }
        tmp = tmp->next;
    }
}

void        begin(int argc, char **argv, t_data *data)
{
    fill_data_contents(data);
    hub(argc, argv, data);
}