#include "./../include/ft_ssl.h"

t_bin *new_bin(uint8_t *binary, uint32_t size) {
    t_bin *bin;

    bin = malloc(sizeof(t_bin));
    if(bin == NULL)
        exit_error(MALLOC_ERROR);
    bin->binary = binary;
    bin->size = size;
    return (bin);
}

static void set_size(t_node *node) {
    int fd = open((char*)node->file_name, O_RDONLY);
    if(fd < 0)
        return;
    close(fd);
    struct stat file_info;
    stat((char*)node->file_name, &file_info);
    node->file_size = (uint32_t)file_info.st_size;
}

t_node *new_node(uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node;

    node = malloc(sizeof(t_node));
    if(node == NULL)
        exit_error(MALLOC_ERROR);
    node->type = type;
    node->arg = arg ? (uint8_t*)strdup((char*)arg): NULL;
    node->file_name = file_name ? (uint8_t*)strdup((char*)file_name): NULL;
    if(type == FILE)
        set_size(node);
    if(type == STRING)
        node->file_size = ft_strlen(arg);
    node->next = NULL;
    return (node);
}

t_node *node_last(t_node *node) {
    while (node && node->next) {
        node = node->next;
    }
    return (node);
}

void node_add_back(t_node **head, t_node *new) {
    if (head != 0)
	{
		if (*head && new != 0)
			node_last(*head)->next = new;
		else
			*head = new;
	}
}

t_command *new_command(uint8_t *name, void (*hash)(int, char**, t_data*)) {
    t_command *command;

    command = malloc(sizeof(t_command));
    if(command == NULL)
        exit_error(MALLOC_ERROR);
    command->name = name ? (uint8_t*)strdup((char*)name): NULL;
    command->hash = hash;
    command->next = NULL;
    return (command);
}

t_command *command_last(t_command *command) {
    while (command && command->next) {
        command = command->next;
    }
    return (command);
}

void command_add_back(t_command **head, t_command *new) {
    if (head != 0)
	{
		if (*head && new != 0)
			command_last(*head)->next = new;
		else
			*head = new;
	}
}