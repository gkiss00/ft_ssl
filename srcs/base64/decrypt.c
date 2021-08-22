#include "./../include/ft_ssl.h"

uint8_t MAP[128] = {
    'A', 0, 'B', 1, 'C', 2, 'D', 3, 'E', 4, 'F', 5, 'G', 6, 'H', 7,
    'I', 8, 'J', 9, 'K', 10, 'L', 11, 'M', 12, 'N', 13, 'O', 14, 'P', 15,
    'Q', 16, 'R', 17, 'S', 18, 'T', 19, 'U', 20, 'V', 21, 'W', 22, 'X', 23,
    'Y', 24, 'Z', 25, 'a', 26, 'b', 27, 'c', 28, 'd', 29, 'e', 30, 'f', 31,
    'g', 32, 'h', 33, 'i', 34, 'j', 35, 'k', 36, 'l', 37, 'm', 38, 'n', 39,
    'o', 40, 'p', 41, 'q', 42, 'r', 43, 's', 44, 't', 45, 'u', 46, 'v', 47,
    'w', 48, 'x', 49, 'y', 50, 'z', 51, '0', 52, '1', 53, '2', 54, '3', 55,
    '4', 56, '5', 57, '6', 58, '7', 59, '8', 60, '9', 61, '+', 62, '/', 63
};

static uint8_t mapping(uint8_t c) {
    for (uint32_t i = 0;i < 128; i += 2) {
        if (MAP[i] == c){
            return MAP[i + 1];
        }
    }
    return 0;
}

static uint32_t get_rest1(uint8_t *msg) {
    uint32_t size = ft_strlen(msg);
    uint32_t rest = 0;
    for (uint32_t i = size -1; i >= 0; --i){
        if (msg[i] == '=')
            ++rest;
        else
            break;
    }
    return rest;
}

static uint32_t get_rest(uint32_t i, uint32_t nb_block, uint8_t *msg) {
    uint32_t rest = 0;
    if (i == nb_block - 1) {
        rest = get_rest1(msg);
    }
    return rest;
}

static uint32_t get_nb_block(uint32_t size) {
    uint32_t nb_block = (size / 4);
    return nb_block;
}

static uint32_t get_new_size(uint32_t size, uint8_t *msg) {
    uint32_t rest = get_rest1(msg);
    uint32_t new_size = 0;
    new_size = (size / 4) * 3;
    if(rest == 1)
        --size;
    if (rest == 2)
        size -= 2;
    return new_size + 1;
}

uint8_t *decrypt_base64(uint8_t *msg) {
    uint32_t size = ft_strlen(msg);
    uint32_t new_size = get_new_size(size, msg);
    uint32_t nb_block = get_nb_block(size);
    uint8_t *new_msg = malloc(new_size);
    memset(new_msg, 0, new_size);

    if(new_msg == NULL){
        printf("Malloc error");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < nb_block; ++i) {
        uint32_t rest = get_rest(i, nb_block, msg);

        uint8_t block[4];
        block[0] =  mapping(msg[(i * 4) + 0]);
        block[1] =  mapping(msg[(i * 4) + 1]);
        block[2] =  mapping(msg[(i * 4) + 2]);
        block[3] =  mapping(msg[(i * 4) + 3]);
        
        uint8_t new_block[3];
        
        switch (rest)
        {
            case 0:
                new_block[0] = (uint8_t)((uint8_t)(block[0] << 2) | (uint8_t)(block[1] >> 4));
                new_block[1] = (uint8_t)((uint8_t)(block[1] << 4) | (uint8_t)(block[2] >> 2));
                new_block[2] = (uint8_t)((uint8_t)(block[2] << 6) | (uint8_t)(block[3]));
                memcpy(&new_msg[(i * 3) + 0], &new_block[0], 1);
                memcpy(&new_msg[(i * 3) + 1], &new_block[1], 1);
                memcpy(&new_msg[(i * 3) + 2], &new_block[2], 1);
                break;
            case 1:
                new_block[0] = (uint8_t)((uint8_t)(block[0] << 2) | (uint8_t)(block[1] >> 4));
                new_block[1] = (uint8_t)((uint8_t)(block[1] << 4) | (uint8_t)(block[2] >> 2));
                memcpy(&new_msg[(i * 3) + 0], &new_block[0], 1);
                memcpy(&new_msg[(i * 3) + 1], &new_block[1], 1);
                break;
            case 2:
                new_block[0] = (uint8_t)((uint8_t)(block[0] << 2) | (uint8_t)(block[1] >> 4));
                memcpy(&new_msg[(i * 3) + 0], &new_block[0], 1);
                break;
            default:
                break;
        }
    }
    return (new_msg);
}