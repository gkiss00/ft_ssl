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

static int shift_table[16] = { 1, 1, 2, 2,
                        2, 2, 2, 2,
                        1, 2, 2, 2,
                        2, 2, 2, 1 };

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

// permutate block from 64 to 64
static void permutate_block_64_to_64(uint8_t *block) {
    uint8_t permutated_block[8];

    memset(permutated_block, 0, 8); // set memory to 0
    for (int j = 0; j < 8; ++j) // for each res
    {
        for (int k = 0; k < 8; ++k) // for each bits
        {
            int l = 8*j + k; // get the current index
            int shift = block_permutation_table[l] - 1; // get the shift
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

static void combine(uint8_t *res, uint8_t working, uint8_t table[4][16]) {
    uint8_t x;
    uint8_t y;

    x = X(working);
    y = Y(working);
    printf("%d %d\n", (int)x, (int)y);
    *res = table[y][x];
    PRINT_UINT8(res); puts("");
}

// 48 bits to 32 bits
static void s_box(uint8_t block[6], uint8_t res[4]) {
    uint8_t tmp[8];
    uint8_t working;

    working = (block[0] >> 2);
    combine(&tmp[0], working, s_box_table[0]);

    working = ((block[0] << 6) >> 2) | (block[1] >> 4);
    // PRINT_UINT8(&block[0]); puts("");
    // PRINT_UINT8(&block[1]); puts("");
    // PRINT_UINT8(&working); puts("");
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
    nb_block = (size / 64) + (size % 64 == 0 ? 0 : 1);
    return nb_block;
}

static void get_keys(
    uint8_t key_64[8], 
    uint8_t key_56[7],
    uint8_t key_56_table[16][7], 
    uint8_t key_48_table[16][6]
) {
    printf("key 64: ");
    PRINT_UINT64(key_64);
    puts("");

    memset(key_56, 0, 7);
    permutate_key_64_to_56(key_64, key_56); // ok

    printf("key 56: ");
    PRINT_UINT56(key_56);
    puts("");

    for (int i = 0; i < 16; ++i) {
        if(i == 0)
            memcpy(key_56_table[i], key_56, 7);
        else
            memcpy(key_56_table[i], key_56_table[i - 1], 7);
        rotate_key(key_56_table[i], shift_table[i]);

        printf("key 56 %d: ", i);
        PRINT_UINT56(key_56_table[i]);
        puts("");
    }

    for(int i = 0; i < 16; ++i) {
        permutate_key_56_to_48(key_56_table[i], key_48_table[i]);

        printf("key 48 %d: ", i);
        PRINT_UINT48(key_48_table[i]);
        puts("");
    }
}

static void xor(uint8_t *ptr1, uint8_t *ptr2, int size) {
    for (int i = 0; i < size; ++i) {
        ptr1[i] = XOR(ptr1[i], ptr2[i]);
    }
}

static void ft_encrypt(uint8_t *msg, uint8_t key_64[8]) {
    uint8_t key_56[7];
    uint8_t key_56_table[16][7];
    uint8_t key_48_table[16][6];

    get_keys(key_64, key_56, key_56_table, key_48_table);

    int nb_block = (int)get_nb_block(msg);
    printf("nb block : %d\n", nb_block);
    for (int i = 0; i < nb_block; ++i) {
        uint8_t block[8];
        memcpy(block, &msg[i * 8], 8);

        printf("block %d: ", i);
        PRINT_UINT64(block);
        puts("");

        permutate_block_64_to_64(block);

        printf("block permuted %d: ", i);
        PRINT_UINT64(block);
        puts("");

        uint8_t left_32[16][4];
        uint8_t right_32[16][4];
        memcpy(left_32[0], &block[0], 4);
        memcpy(right_32[0], &block[4], 4);

        for (int k = 0; k < 1; ++k) {
            uint8_t left_48[6];
            uint8_t right_48[6];
            uint8_t res[4];

            permutate_block_32_to_48(right_32[k], right_48);
            xor(right_48, key_48_table[k], 6);
            s_box(right_48, res);
            permutate_s_box_32_to_32(res); // ok

            printf("block s_box permutated %d: ", k);
            PRINT_UINT32(res);
            puts("");
        }
    }
}

void ft_des(int argc, char **argv, t_data *data) {
    uint8_t key[8] = { 19, 52, 87, 121, 155, 188, 223, 241 };
    uint8_t msg[8] = { 1, 35, 69, 103, 137, 171, 205, 239 };
    parsing_cipher(argc, argv, data);
    if (data->node == NULL)
        get_stdin_input(data);
    fill_data_contents(data);
    ft_encrypt(msg, key);
    printf("END\n");
}