#include "./../include/ft_ssl.h"

uint32_t KK[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t    H[8];

static void preprocessing(uint8_t *msg, uint8_t *chunk) {
    uint32_t len = strlen((char*)msg);
    uint32_t nb_chunk = (len / 64) + 1 + ((len % 64) >= 56 ? 1 : 0);
    uint64_t size = small_to_big_endian_64(len * 8);

    memset(chunk, 0, nb_chunk * 64);
    memcpy(chunk, msg, len);
    chunk[len] = 1 << 7;
    memcpy(&chunk[(nb_chunk * 64) - 8], &size, sizeof size);
}

static void hash_chunk(uint8_t *chunk) {
    uint32_t W[64] = {0};

    for (uint32_t i = 0; i < 16; ++i) {
        int j = 4 * i;
        W[i] = (chunk[j] << 24) + (chunk[j + 1] << 16) + (chunk[j + 2] << 8) + chunk[j + 3];
    }

    for (uint32_t i = 16; i < 64; ++i) {
        
        uint32_t S0 = right_rotate_32(W[i - 15], 7) ^ right_rotate_32(W[i - 15], 18) ^ (W[i - 15] >> 3);
        uint32_t S1 = right_rotate_32(W[i - 2], 17) ^ right_rotate_32(W[i - 2], 19) ^ (W[i - 2] >> 10);
        W[i] = W[i - 16] + S0 + W[i - 7] + S1;
    }

    uint32_t a = H[0];
    uint32_t b = H[1];
    uint32_t c = H[2];
    uint32_t d = H[3];
    uint32_t e = H[4];
    uint32_t f = H[5];
    uint32_t g = H[6];
    uint32_t h = H[7];

    for (uint32_t i = 0; i < 64; ++i) {
        uint32_t S1 = right_rotate_32(e, 6) ^ right_rotate_32(e, 11) ^ right_rotate_32(e, 25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t temp1 = h + S1 + ch + KK[i] + W[i];
        uint32_t S0 = right_rotate_32(a, 2) ^ right_rotate_32(a, 13) ^ right_rotate_32(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;

}

void        hash_sha256(uint8_t *msg, uint8_t *hashed, uint32_t size){
    uint32_t nb_chunk = (size / 64) + 1 + ((size % 64) >= 56 ? 1 : 0);
    uint8_t chunk[nb_chunk * 64];

    preprocessing(msg, chunk);

    H[0] = 0x6a09e667;
    H[1] = 0xbb67ae85;
    H[2] = 0x3c6ef372;
    H[3] = 0xa54ff53a;
    H[4] = 0x510e527f;
    H[5] = 0x9b05688c;
    H[6] = 0x1f83d9ab;
    H[7] = 0x5be0cd19;

    for (uint32_t i = 0; i < nb_chunk; ++i) {
        hash_chunk(&chunk[i * 64]);
    }

    for (uint32_t i = 0; i < 8; ++i) {
        H[i] = big_to_small_endian_32(H[i]);
    }

    memcpy(&hashed[0], &H[0], sizeof(H[0]));
    memcpy(&hashed[4], &H[1], sizeof(H[1]));
    memcpy(&hashed[8], &H[2], sizeof(H[2]));
    memcpy(&hashed[12], &H[3], sizeof(H[3]));
    memcpy(&hashed[16], &H[4], sizeof(H[4]));
    memcpy(&hashed[20], &H[5], sizeof(H[5]));
    memcpy(&hashed[24], &H[6], sizeof(H[6]));
    memcpy(&hashed[28], &H[7], sizeof(H[7]));
}