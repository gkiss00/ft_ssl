#include "./../include/ft_ssl.h"

static int key_permutation_table1[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

static int key_permutation_table2[48] = { 
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32 
};

static int block_permutation_table[64] = { 
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 
};

static int block_final_permutation_table[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};

static int e_bit_table[48] = {
    32, 1, 2, 3, 4, 5,
     4, 5, 6, 7, 8, 9,
     8, 9, 10, 11 ,12 ,13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};

static int s_box_permutation_table[32] = {
    16,   7,  20,  21,
    29,  12,  28,  17,
     1,  15,  23,  26,
     5,  18,  31,  10,
     2,   8,  24,  14,
    32,  27,   3,   9,
    19,  13,  30,   6,
    22,  11,   4,  25,
};

static int shift_table[16] = { 
    1, 1, 2, 2,
    2, 2, 2, 2,
    1, 2, 2, 2,
    2, 2, 2, 1 
};

// S-box Table
static uint8_t s_box_table[8][4][16] = { 
    { 
        { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
        { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
        { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
        { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
    },
    { 
        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
        { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
        { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
        { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
    },
    { 
        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
        { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
        { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
        { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
    },
    { 
        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
        { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
        { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
        { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
    },
    { 
        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
        { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
        { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
        { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
    },
    { 
        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
        { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
        { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
        { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
    },
    { 
        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
        { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
        { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
        { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
    },
    { 
        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
        { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
        { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
        { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
    }
};


// permutate block from 64 to 64
static void permutate_block_64_to_64(uint8_t *block, int table[64]) {
    uint8_t permutated_block[8];

    memset(permutated_block, 0, 8); // set memory to 0
    for (int j = 0; j < 8; ++j) // for each res
    {
        for (int k = 0; k < 8; ++k) // for each bits
        {
            int l = 8*j + k; // get the current index
            int shift = table[l] - 1; // get the shift
            int bit = (block[shift / 8] >> (7 - shift%8)) & 1; // set the bit to 0 or 1
            permutated_block[j] |= bit << (7 - k); // add to new value
        }
    }
    memcpy(block, permutated_block, 8);
}

// permutate block from 32 to 48
static void permutate_block_32_to_48(uint8_t *block_32, uint8_t block_48[6]) {
    uint8_t permutated_block[6];

    memset(permutated_block, 0, 6); // set memory to 0
    for (int j = 0; j < 6; ++j) // for each res
    {
        for (int k = 0; k < 8; ++k) // for each bits
        {
            int l = 8*j + k; // get the current index
            int shift = e_bit_table[l] - 1; // get the shift
            int bit = (block_32[shift / 8] >> (7 - shift%8)) & 1; // set the bit to 0 or 1
            permutated_block[j] |= bit << (7 - k); // add to new value
        }
    }
    memcpy(block_48, permutated_block, 6);
}

// permutate s_box output from 32 to 32
static void permutate_s_box_32_to_32(uint8_t *s_box_32) {
    uint8_t permutated_block[4];

    memset(permutated_block, 0, 4); // set memory to 0
    for (int j = 0; j < 4; ++j) // for each res
    {
        for (int k = 0; k < 8; ++k) // for each bits
        {
            int l = 8*j + k; // get the current index
            int shift = s_box_permutation_table[l] - 1; // get the shift
            int bit = (s_box_32[shift / 8] >> (7 - shift%8)) & 1; // set the bit to 0 or 1
            permutated_block[j] |= bit << (7 - k); // add to new value
        }
    }
    memcpy(s_box_32, permutated_block, 4);
}

// permutate key from 64 to 56
static void permutate_key_64_to_56(uint8_t key_64[8], uint8_t key_56[7]) {
    uint8_t permutated_key[7];

    memset(permutated_key, 0, 7); // set memory to 0
    for (int j = 0; j < 7; ++j) // for each res
    {
        for (int k = 0; k < 8; ++k) // for each bits
        {
            int l = 8*j + k; // get the current index
            int shift = key_permutation_table1[l] - 1; // get the shift
            int bit = (key_64[shift / 8] >> (7 - shift%8)) & 1; // set the bit to 0 or 1
            permutated_key[j] |= bit << (7 - k); // add to new value
        }
    }
    memcpy(key_56, permutated_key, 7);
}

// permutate key from 56 to 48
static void permutate_key_56_to_48(uint8_t key_56[7], uint8_t key_48[6]) {
    uint8_t permutated_key[6];

    memset(permutated_key, 0, 6);
    for (int j = 0; j < 6; ++j)
    {
        for (int k = 0; k < 8; ++k)
        {
            int l = 8*j + k;
            int shift = key_permutation_table2[l] - 1;
            int bit = (key_56[shift / 8] >> (7 - shift%8)) & 1;
            permutated_key[j] |= bit << (7 - k);
        }
    }
    memcpy(key_48, permutated_key, 6);
}

// left rotate key
static void rotate_key(uint8_t key[7], int shift) {
    uint8_t left[4];
    uint8_t right[4];
    uint8_t save;

    memcpy(left, key, 4);
    memcpy(right, &key[3], 4);

    left[3] = (uint8_t)((uint8_t)(left[3] >> 4) << 4); // 11111111 11111111 11111111 11110000 
    right[0] = (uint8_t)((uint8_t)(right[0] << 4) >> 4); // 00001111 111111111 11111111 11111111 

    save = left[0];

    left[0] = (uint8_t)((uint8_t)(left[0] << shift) | (uint8_t)(left[1] >> (8 - shift)));
    left[1] = (uint8_t)((uint8_t)(left[1] << shift) | (uint8_t)(left[2] >> (8 - shift)));
    left[2] = (uint8_t)((uint8_t)(left[2] << shift) | (uint8_t)(left[3] >> (8 - shift)));
    left[3] = (uint8_t)((uint8_t)(left[3] << shift) | (uint8_t)((uint8_t)(save >> (8 - shift)) << 4));

    save = right[0];

    right[0] = (uint8_t)((uint8_t)((uint8_t)((uint8_t)(right[0] << shift) | (uint8_t)(right[1] >> (8 - shift))) << 4) >> 4);
    right[1] = (uint8_t)((uint8_t)(right[1] << shift) | (uint8_t)(right[2] >> (8 - shift)));
    right[2] = (uint8_t)((uint8_t)(right[2] << shift) | (uint8_t)(right[3] >> (8 - shift)));
    right[3] = (uint8_t)((uint8_t)(right[3] << shift) | (uint8_t)(save >> (4 - shift)));

    memcpy(key, left, 3);
    key[3] = left[3] | right[0];
    memcpy(&key[4], &right[1], 3);
}

static void combine(uint8_t *res, uint8_t working, uint8_t table[4][16]) {
    uint8_t x;
    uint8_t y;

    x = X(working);
    y = Y(working);
    *res = table[y][x];
}

// 48 bits to 32 bits
static void s_box(uint8_t block[6], uint8_t res[4]) {
    uint8_t tmp[8];
    uint8_t working;

    working = (block[0] >> 2);
    combine(&tmp[0], working, s_box_table[0]);

    working = ((block[0] << 6) >> 2) | (block[1] >> 4);
    combine(&tmp[1], working, s_box_table[1]);

    working = ((block[1] << 4) >> 2) | (block[2] >> 6);
    combine(&tmp[2], working, s_box_table[2]);

    working = ((block[2] << 2) >> 2);
    combine(&tmp[3], working, s_box_table[3]);

    working = (block[3] >> 2);
    combine(&tmp[4], working, s_box_table[4]);

    working = ((block[3] << 6) >> 2) | (block[4] >> 4);
    combine(&tmp[5], working, s_box_table[5]);

    working = ((block[4] << 4) >> 2) | (block[5] >> 6);
    combine(&tmp[6], working, s_box_table[6]);

    working = ((block[5] << 2) >> 2);
    combine(&tmp[7], working, s_box_table[7]);

    res[0] = (tmp[0] << 4) | tmp[1];
    res[1] = (tmp[2] << 4) | tmp[3];
    res[2] = (tmp[4] << 4) | tmp[5];
    res[3] = (tmp[6] << 4) | tmp[7];
}

static uint32_t get_nb_block(uint8_t *msg) {
    uint32_t size;
    uint32_t nb_block;

    size = ft_strlen(msg);
    nb_block = (size / 8) + (size % 8 == 0 ? 0 : 1);
    return nb_block;
}

static void get_keys(
    uint8_t key_64[8],
    uint8_t key_48_table[16][6]
) {
    uint8_t key_56[7];
    uint8_t key_56_table[16][7];

    memset(key_56, 0, 7);
    permutate_key_64_to_56(key_64, key_56);

    for (int i = 0; i < 16; ++i) {
        if(i == 0)
            memcpy(key_56_table[i], key_56, 7);
        else
            memcpy(key_56_table[i], key_56_table[i - 1], 7);
        rotate_key(key_56_table[i], shift_table[i]);
        permutate_key_56_to_48(key_56_table[i], key_48_table[i]);
    }
}

static void xor(uint8_t *ptr1, uint8_t *ptr2, int size) {
    for (int i = 0; i < size; ++i) {
        ptr1[i] = XOR(ptr1[i], ptr2[i]);
    }
}

static void add(uint8_t *ptr1, uint8_t *ptr2, uint8_t *res) {
    uint32_t *t1 = (uint32_t*)ptr1;
    uint32_t *t2 = (uint32_t*)ptr2;
    uint32_t t3 = *t1 ^ *t2;
    memcpy(res, &t3, 4);
}

static void ft_encrypt(uint8_t *msg, uint8_t key_64[8]) {
    int nb_block;
    uint8_t key_48_table[16][6];

    nb_block  = (int)get_nb_block(msg);
    get_keys(key_64, key_48_table);

    for (int i = 0; i < nb_block; ++i) {
        uint8_t block[8];
        uint8_t left_32_table[17][4];
        uint8_t right_32_table[17][4];

        memcpy(block, &msg[i * 8], 8);
        permutate_block_64_to_64(block, block_permutation_table);
        memcpy(left_32_table[0], &block[0], 4);
        memcpy(right_32_table[0], &block[4], 4);

        for (int k = 0; k < 16; ++k) {
            uint8_t right_48[6];
            uint8_t s_box_output[4];

            if(k != 0)
                memcpy(left_32_table[k], right_32_table[k - 1], 4);
            permutate_block_32_to_48(right_32_table[k], right_48);
            xor(right_48, key_48_table[k], 6);
            s_box(right_48, s_box_output);
            permutate_s_box_32_to_32(s_box_output);
            add(left_32_table[k], s_box_output, right_32_table[k + 1]);   
        }
        uint8_t final_block[8];

        memcpy(left_32_table[16], right_32_table[15], 4);  
        memcpy(&final_block[0], &right_32_table[16], 4);
        memcpy(&final_block[4], &left_32_table[16], 4);
        permutate_block_64_to_64(final_block, block_final_permutation_table);
        memcpy(&msg[i * 8], final_block, 8);
    }
}

void ft_des(int argc, char **argv, t_data *data) {
    parsing_cipher(argc, argv, data);
    if (data->node == NULL)
        get_stdin_input(data);
    fill_data_contents(data);
    pre_process(data);
    
    int nb_block = (int)get_nb_block(data->node->arg);
    // for(int i = 0; i < nb_block; ++i) {
    //     PRINT_UINT64(&data->node->arg[i * 8]);
    //     puts("");
    // }
    // printf("%d\n", (int)ft_strlen(data->node->arg));
    // printf("%d\n", nb_block);
    ft_encrypt(data->node->arg, data->opts_cipher->key);
    write(1, data->node->arg, nb_block * 8);
    // puts("");
    // for(int i = 0; i < nb_block; ++i) {
    //     PRINT_UINT64(&data->node->arg[i * 8]);
    //     puts("");
    // }
}