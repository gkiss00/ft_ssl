#include "./../include/ft_ssl.h"

uint8_t ALPHA[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/',
};

uint8_t cpm = '=';

static uint32_t get_rest(uint32_t i, uint32_t nb_block, uint32_t size) {
    uint32_t rest = 0;
    if (i == nb_block - 1) {
        rest = size % 3;
    }
    return rest;
}

static uint32_t get_nb_block(uint32_t size) {
    uint32_t nb_block = (size / 3) + (size % 3 == 0 ? (0) : (1));
    return nb_block;
}

static uint32_t get_new_size(uint32_t size) {
    uint32_t new_size = 0;
    new_size = ((size / 3) * 4) + (size % 3 == 0 ? (0) : (4));
    return new_size + 1;
}

uint8_t *encrypt_base64(uint8_t *msg, uint32_t size) {
    uint32_t new_size = get_new_size(size);
    uint32_t nb_block = get_nb_block(size);
    uint8_t *new_msg = calloc(new_size, 1);

    if(new_msg == NULL)
        exit_error(MALLOC_ERROR);
    
    for (uint32_t i = 0; i < nb_block; ++i) {
        uint32_t rest = get_rest(i, nb_block, size);

        uint8_t block[3];
        memset(block, 0, 3);
        if (rest == 0)
            memcpy(block, &msg[i * 3], 3);
        if (rest == 1)
            memcpy(block, &msg[i * 3], 1);
        if (rest == 2)
            memcpy(block, &msg[i * 3], 2);
        
        uint8_t new_block[4];
        
        switch (rest)
        {
            case 0:
                new_block[0] = block[0] >> 2;
                new_block[1] = (uint8_t)(((uint8_t)(block[0] << 6) >> 2) | (block[1] >> 4));
                new_block[2] = (uint8_t)(((uint8_t)(block[1] << 4) >> 2) | (block[2] >> 6));
                new_block[3] = (uint8_t)((uint8_t)(block[2] << 2) >> 2);
                memcpy(&new_msg[(i * 4) + 0], &ALPHA[new_block[0]], 1);
                memcpy(&new_msg[(i * 4) + 1], &ALPHA[new_block[1]], 1);
                memcpy(&new_msg[(i * 4) + 2], &ALPHA[new_block[2]], 1);
                memcpy(&new_msg[(i * 4) + 3], &ALPHA[new_block[3]], 1);
                break;
            case 1:
                new_block[0] = block[0] >> 2;
                new_block[1] = (uint8_t)(((uint8_t)(block[0] << 6) >> 2) | 0);
                memcpy(&new_msg[(i * 4) + 0], &ALPHA[new_block[0]], 1);
                memcpy(&new_msg[(i * 4) + 1], &ALPHA[new_block[1]], 1);
                memcpy(&new_msg[(i * 4) + 2], &cpm, 1);
                memcpy(&new_msg[(i * 4) + 3], &cpm, 1);
                break;
            case 2:
                new_block[0] = block[0] >> 2;
                new_block[1] = (uint8_t)(((uint8_t)(block[0] << 6) >> 2) | (block[1] >> 4));
                new_block[2] = (uint8_t)(((uint8_t)(block[1] << 4) >> 2) | 0);
                memcpy(&new_msg[(i * 4) + 0], &ALPHA[new_block[0]], 1);
                memcpy(&new_msg[(i * 4) + 1], &ALPHA[new_block[1]], 1);
                memcpy(&new_msg[(i * 4) + 2], &ALPHA[new_block[2]], 1);
                memcpy(&new_msg[(i * 4) + 3], &cpm, 1);
                break;
            default:
                break;
        }
    }
    return (new_msg);
}