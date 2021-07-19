#include "./../include/ft_ssl.h"

t_command   *init_cmd(){
    t_command *cmd = new_command((uint8_t*)"md5", &ft_md5);
    command_add_back(&cmd, new_command((uint8_t*)"sha256", &ft_sha256));

    return cmd;
}

void        hub(t_data *data)
{
    t_command *cmd = init_cmd();
    while(cmd) {
        if (ft_strcmp(data->cmd, cmd->name) == 0){
            cmd->hash(data);
            break;
        }
        cmd = cmd->next;
    }
}