#include "./../include/ft_ssl.h"

t_command   *init_cmd(){
    t_command *cmd = new_command((uint8_t*)"md5", &ft_md5);
    command_add_back(&cmd, new_command((uint8_t*)"sha256", &ft_sha256));
    command_add_back(&cmd, new_command((uint8_t*)"base64", &ft_base64));

    return cmd;
}

void        hub(int argc, char **argv, t_data *data)
{
    t_command *cmd = init_cmd();
    while(cmd) {
        if (ft_strcmp(data->cmd, cmd->name) == 0){
            cmd->hash(argc, argv, data);
            break;
        }
        cmd = cmd->next;
    }
    if(cmd == NULL)
        print_usage_error(argv);
}