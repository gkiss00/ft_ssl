#include "./../include/ft_ssl.h"

int permutation_table[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                            60, 52, 44, 36, 28, 20, 12, 4,
                            62, 54, 46, 38, 30, 22, 14, 6,
                            64, 56, 48, 40, 32, 24, 16, 8,
                            57, 49, 41, 33, 25, 17, 9, 1,
                            59, 51, 43, 35, 27, 19, 11, 3,
                            61, 53, 45, 37, 29, 21, 13, 5,
                            63, 55, 47, 39, 31, 23, 15, 7 };

int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                    3, 28, 15, 6, 21, 10,
                    23, 19, 12, 4, 26, 8,
                    16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32 };

int shift_table[16] = { 1, 1, 2, 2,
                        2, 2, 2, 2,
                        1, 2, 2, 2,
                        2, 2, 2, 1 };

// S-box Table
uint8_t s[8][4][16] = { { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                    { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                    { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                    { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }},

                    // X 00011110 2 4 8 16 => 1 2 4 8
                    // Y 00100001 1 32 => 

                    { 
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                        { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                        { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                        { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
                    },
 
                    { { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                    { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                    { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                    { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }},

                    { { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                    { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                    { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                    { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }},

                    { { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                    { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                    { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                    { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }},

                    { { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                    { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                    { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                    { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }},

                    { { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                    { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                    { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                    { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }},

                    { { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                    { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                    { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                    { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }}
                };

// 64 bits key to 56 bits key
static void key_from_64_to_56(uint8_t key[8], uint8_t res[7]) {
    for(int i = 0; i < 8; ++i) {
        key[i] = (key[i] >> 1) << 1;
    }
    for(int i = 0; i < 7; ++i) {
        res[i] = (key[i] << i) | (key[i + 1] >> (8 - i + 1));
    }
}

// left rotate key
static void rotate_key(uint8_t key[7], int shift) {
    uint8_t left[4];
    uint8_t right[4];
    uint8_t save;

    memcpy(left, key, 4);
    memcpy(right, &key[3], 4);

    left[3] = (left[3] >> 4) << 4; // 11111111 11111111 11111111 11110000 
    right[0] = (right[0] << 4) >> 4; // 00001111 111111111 11111111 11111111 

    save = left[0];

    left[0] = (left[0] << shift) | (left[1] >> (8 - shift));
    left[1] = (left[1] << shift) | (left[2] >> (8 - shift));
    left[2] = (left[2] << shift) | (left[3] >> (8 - shift));
    left[3] = (left[3] << shift) | ((save >> (8 - shift)) << 4);

    save = right[0];

    right[0] = (((right[0] << shift) | (right[1] >> (8 - shift))) << 4) >> 4;
    right[1] = (right[1] << shift) | (right[2] >> (8 - shift));
    right[2] = (right[2] << shift) | (right[3] >> (8 - shift));
    right[3] = (right[3] << shift) | (right[0] >> (4 - shift));

    memcpy(key, left, 3);
    key[3] = left[3] | right[0];
    memcpy(&key[4], &right[1], 3);
}

static void key_from_56_to_48(uint8_t key[7], uint8_t res[6]) {
    uint64_t tmp;
    uint64_t save;

    memset(&tmp, 0, 8);

    memset(&save, 0, 8);
    memcpy(&save, key, 7);

    for (int i = 0; i < 48; ++i) {
        tmp |= BIT(save, key_comp[i]) << (47 - i);
    }

    memcpy(res, &tmp, 6); // maybe should be shifted
}

// initial permutation on block
static void initial_permutation(uint8_t msg[8]) {
    uint64_t tmp;
    uint64_t save;

    memset(&tmp, 0, 8);
    memcpy(&save, msg, 8);
    for (int i = 0; i < 64; ++i) {
        tmp |= BIT(save, permutation_table[i]) << (63 - i);
    }
    memcpy(msg, &tmp, 8);
}

static void expand_block(uint8_t expanded_rblock[6], uint32_t rblock)
{
    expanded_rblock[0] |= BIT(rblock, 0) << 6;
    expanded_rblock[0] |= BIT(rblock, 1) << 5;
    expanded_rblock[0] |= BIT(rblock, 2) << 4;
    expanded_rblock[0] |= BIT(rblock, 3) << 3;
    expanded_rblock[0] |= BIT(rblock, 4) << 2;

    expanded_rblock[0] |= BIT(rblock, 3) << 1;
    expanded_rblock[0] |= BIT(rblock, 4);
    expanded_rblock[1] |= BIT(rblock, 5) << 7;
    expanded_rblock[1] |= BIT(rblock, 6) << 6;
    expanded_rblock[1] |= BIT(rblock, 7) << 5;
    expanded_rblock[1] |= BIT(rblock, 8) << 4;

    expanded_rblock[1] |= BIT(rblock, 7) << 3;
    expanded_rblock[1] |= BIT(rblock, 8) << 2;
    expanded_rblock[1] |= BIT(rblock, 9) << 1;
    expanded_rblock[1] |= BIT(rblock, 10);
    expanded_rblock[2] |= BIT(rblock, 11) << 7;
    expanded_rblock[2] |= BIT(rblock, 12) << 6;

    expanded_rblock[2] |= BIT(rblock, 11) << 5;
    expanded_rblock[2] |= BIT(rblock, 12) << 4;
    expanded_rblock[2] |= BIT(rblock, 13) << 3;
    expanded_rblock[2] |= BIT(rblock, 14) << 2;
    expanded_rblock[2] |= BIT(rblock, 15) << 1;
    expanded_rblock[2] |= BIT(rblock, 16);

    expanded_rblock[3] |= BIT(rblock, 15) << 7;
    expanded_rblock[3] |= BIT(rblock, 16) << 6;
    expanded_rblock[3] |= BIT(rblock, 17) << 5;
    expanded_rblock[3] |= BIT(rblock, 18) << 4;
    expanded_rblock[3] |= BIT(rblock, 19) << 3;
    expanded_rblock[3] |= BIT(rblock, 20) << 2;

    expanded_rblock[3] |= BIT(rblock, 19) << 1;
    expanded_rblock[3] |= BIT(rblock, 20);
    expanded_rblock[4] |= BIT(rblock, 21) << 7;
    expanded_rblock[4] |= BIT(rblock, 22) << 6;
    expanded_rblock[4] |= BIT(rblock, 23) << 5;
    expanded_rblock[4] |= BIT(rblock, 24) << 4;

    expanded_rblock[4] |= BIT(rblock, 23) << 3;
    expanded_rblock[4] |= BIT(rblock, 24) << 2;
    expanded_rblock[4] |= BIT(rblock, 25) << 1;
    expanded_rblock[4] |= BIT(rblock, 26);
    expanded_rblock[5] |= BIT(rblock, 27) << 7;
    expanded_rblock[5] |= BIT(rblock, 28) << 6;

    expanded_rblock[5] |= BIT(rblock, 27) << 5;
    expanded_rblock[5] |= BIT(rblock, 28) << 4;
    expanded_rblock[5] |= BIT(rblock, 29) << 3;
    expanded_rblock[5] |= BIT(rblock, 30) << 2;
    expanded_rblock[5] |= BIT(rblock, 31) << 1;
    expanded_rblock[5] |= BIT(rblock, 0);
}

static void combine(uint8_t *res, uint8_t working, uint8_t table[4][16]) {
    uint8_t x;
    uint8_t y;

    x = X(working);
    y = Y(working);
    *res = table[y][x];
}

// 48 bits to 32 bits
static void s_box(uint8_t block[6], uint8_t res[4], uint8_t table[4][16]) {
    uint8_t tmp[8];
    uint8_t working;

    working = (block[0] >> 2);
    combine(&tmp[0], working, table);

    working = ((block[0] << 6) >> 2) & (block[1] >> 4);
    combine(&tmp[1], working, table);

    working = ((block[1] << 4) >> 2) & (block[2] >> 6);
    combine(&tmp[2], working, table);

    working = ((block[2] << 2) >> 2);
    combine(&tmp[3], working, table);

    working = (block[3] >> 2);
    combine(&tmp[4], working, table);

    working = ((block[3] << 6) >> 2) & (block[4] >> 4);
    combine(&tmp[5], working, table);

    working = ((block[4] << 4) >> 2) & (block[5] >> 6);
    combine(&tmp[6], working, table);

    working = ((block[5] << 2) >> 2);
    combine(&tmp[7], working, table);

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

// from the 64 bits key get a 56 bits key
// divide the msg in 64 bits block
// for each block init the permutation on the block
// for i = 0 < 16, rotate the key and make her 48 bits long
static void ft_encrypt(uint8_t *msg, uint8_t key[8]) {
    uint8_t new_key[7];
    uint8_t saved_key[7];
    uint32_t nb_block = get_nb_block(msg);

    printf("key : ");
    print_uint64(*(uint64_t*)&key[0]);
    puts("");

    key_from_64_to_56(key, new_key);
    memcpy(&saved_key, &new_key, 7);

    printf("new : ");
    PRINT_UINT56(new_key);
    puts("");

    for (uint32_t i = 0; i < nb_block; ++i) {
        uint8_t *block;
        uint8_t *left;
        uint8_t *right;
        memcpy(&new_key, &saved_key, 7);
        block = &msg[i * 8];
        initial_permutation(&msg[i * 8]);
        left = &block[0];
        right = &block[4];

        for (int k = 0; k < 16; ++k) {
            uint8_t last_key[6];
            rotate_key(new_key, shift_table[k]);
            key_from_56_to_48(new_key, last_key);

            // printf("rotated at %d : ", k);
            // PRINT_UINT56(new_key);
            // puts("");

            // printf("key at %d :", k);
            // PRINT_UINT48(last_key);
            // puts("");

            uint8_t new_left[6] = {0};
            uint8_t new_right[6] = {0};
            expand_block(new_left, *(uint32_t*)left);
            expand_block(new_right, *(uint32_t*)right);

            print_uint8(new_right[0]);
            printf(" ");
            print_uint8(new_right[1]);
            printf(" ");
            print_uint8(new_right[2]);
            printf(" ");
            print_uint8(new_right[3]);
            puts("");

            //XOR
            for (int j = 0; j < 6; ++j){
                new_left[j] = new_left[j] ^ last_key[j];
                new_right[j] = new_right[j] ^ last_key[j];
            }

            // print_uint8(new_right[0]);
            // printf(" ");
            // print_uint8(new_right[1]);
            // printf(" ");
            // print_uint8(new_right[2]);
            // printf(" ");
            // print_uint8(new_right[3]);
            // puts("");
            
            uint8_t res_left[4] = {0};
            uint8_t res_right[4] = {0};

            s_box(new_left, res_left, s[0]);
            s_box(new_right, res_right, s[0]);

            // print_uint8(res_right[0]);
            // printf(" ");
            // print_uint8(res_right[1]);
            // printf(" ");
            // print_uint8(res_right[2]);
            // printf(" ");
            // print_uint8(res_right[3]);
            // puts("");
        }
    }
}

void ft_des(int argc, char **argv, t_data *data) {
    uint8_t key[8];
    for(int i = 0; i < 8; ++i) {
        key[i] = i + 1;
    }
    parsing_cipher(argc, argv, data);
    if (data->node == NULL)
        get_stdin_input(data);
    fill_data_contents(data);
    ft_encrypt(data->input, key);
    printf("END\n");
}