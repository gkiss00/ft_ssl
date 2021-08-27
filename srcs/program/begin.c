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
    if(content == NULL)
        return (uint8_t*)ft_strdup((uint8_t*)"");
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

void        fill_data_contents(t_data *data)
{
    t_node *tmp = data->node;

    while(tmp) {
        if(tmp->type == FILE) {
            tmp->arg = get_fd_content(tmp->file_name);
        }
        tmp = tmp->next;
    }
}

static uint8_t  *get_content_binary(int fd)
{
    int         ret;
    int         size = 0;
    uint8_t     buf[10];
    uint8_t     *content;

    ret = 0;
    content = NULL;
    while((ret = read(fd, buf, 9)) > 0)
    {
        buf[ret] = '\0';
        content = ft_strjoin_2(content, buf, size, ret);
        size += ret;
    }
    close(fd);
    if(content == NULL)
        return (uint8_t*)ft_strdup((uint8_t*)"");
    return (content);
}

static uint8_t *get_fd_content_binary(uint8_t *path)
{
    int     fd;

    fd = open((char*)path, O_RDONLY);
    if (fd == -1)
        return (NULL);
    return (get_content_binary(fd));
}

void        fill_data_contents_binary(t_data *data)
{
    t_node *tmp = data->node;

    while(tmp) {
        if(tmp->type == FILE) {
            tmp->arg = get_fd_content_binary(tmp->file_name);
        }
        tmp = tmp->next;
    }
}