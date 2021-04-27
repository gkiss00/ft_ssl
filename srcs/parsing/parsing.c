#include "./../include/ft_ssl.h"

uint8_t options[4] = "qrsp";

static void addArg(t_data *data, uint32_t type, uint8_t *arg, uint8_t *file_name) {
    t_node *node = new_node(type, arg, file_name);
    node_add_back(&data->node, node);
}

static void addOption(t_data *data, uint8_t *opt) {
    uint32_t i = 1;

    while(opt[i]) {
        if (opt[i] == 'q') {
            data->opts->q = 1;
        } else if (opt[i] == 'r') {
            data->opts->r = 1;
        } else if (opt[i] == 's'){
            data->opts->s = 1;
        } else if (opt[i] == 'p'){
            data->opts->p = 1;
        }
        ++i;
    }
}

static bool isOptionString(uint8_t *arg) {
    return (strchr((char*)arg, 's') != NULL);
}

static bool isOption(uint8_t *arg) {
    return (arg[0] == '-');
}

static void getArgs(t_data *data, uint8_t **argv) {
    uint32_t    i = 2;
    bool        onOptions = true;
    while(argv[i]) {
        if (isOption(argv[i]) && onOptions) {
            addOption(data, argv[i]);
            if (isOptionString(argv[i])) {
                ++i;
                addArg(data, STRING, argv[i], NULL);
            }
        } else {
            addArg(data, FILE, NULL, argv[i]);
            onOptions = false;
        }
        ++i;
    }
}

static void getCmd(t_data *data, uint8_t **argv) {
    data->cmd = (uint8_t*)strdup((char*)argv[1]);
    data->uppercase_cmd = (uint8_t*)to_upper((char*)argv[1]);
}

void parsing(t_data *data, uint8_t **argv) {
    getCmd(data, argv);
    getArgs(data, argv);
}