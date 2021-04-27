#include "./../include/ft_ssl.h"

t_node *new_node(uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node;

    node = malloc(sizeof(t_node));
    node->type = type;
    node->arg = arg ? (uint8_t*)strdup((char*)arg): NULL;
    node->file_name = file_name ? (uint8_t*)strdup((char*)file_name): NULL;
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
		{
			node_last(*head)->next = new;
		}
		else
		{
			*head = new;
		}
	}
}