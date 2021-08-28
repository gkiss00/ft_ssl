#include "./../include/ft_ssl.h"

static void print_usage() {
    printf("md5 sha256: usage:\n");
    printf("\t-p stdin\n");
    printf("\t-q quiet\n");
    printf("\t-r reverse\n");
    printf("\t-s <str> string\n");
}

void    parsing_digest(int argc, char **argv, t_data *data) {
    int i = 0;
    int ret = 0;
    data->opts_digest->hash = ft_strcmp(data->cmd, (uint8_t*)"md5") == 0 ? &hash_md5 : &hash_sha256;
    while((ret = getopt(argc - 1, &argv[1], "qrps:")) != -1) {
        switch(ret){
            case 'q':
                data->opts_digest->q = 1;
                break;
            case 'r':
                data->opts_digest->r = 1;
                break;
            case 'p':
                data->opts_digest->p = 1;
                break;
            case 's':
                data->opts_digest->s = 1;
                add_arg(data, STRING, (uint8_t *)optarg, NULL);
                break;
            case '?':
                print_usage();
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }
    for (i = optind + 1; i < argc; i++){
        add_arg(data, FILE, NULL, (uint8_t *)argv[i]);
    }
}