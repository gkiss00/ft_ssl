#include "./../include/ft_ssl.h"

uint32_t S[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

uint32_t K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

uint32_t    h0;
uint32_t    h1;
uint32_t    h2;
uint32_t    h3;

//Copy the msg
//Add a bit the 1 at then end
//Copy the size of the msg at the end of the chunks

static void preprocessing(uint8_t *msg, uint8_t *chunk) {
    uint32_t len = strlen((char *)msg);
    uint32_t nb_chunk = (len / 64) + 1 + ((len % 64) >= 56 ? 1 : 0);
    uint64_t size = len * 8;

    memset(chunk, 0, nb_chunk * 64);
    memcpy(chunk, msg, len);
    chunk[len] = 1 << 7;
    memcpy(&chunk[(nb_chunk * 64) - 8], &size, sizeof size);
}

static void hash_chunk(uint8_t *chunk) {
    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;

    for (uint32_t i = 0; i < 64; ++i) {
        uint32_t f, g;

        if (i >= 0 && i < 16) {
            f = (b & c) | (~b & d);
            g = i;
        } else if (i >= 16 && i < 32) {
            f = (d & b) | (~d & c);
            g = ((i * 5) + 1) % 16;
        } else if (32 >= 0 && i < 48) {
            f = b ^ c ^ d;
            g = ((i * 3) + 5) % 16;
        } else {
            f = c ^ (b | ~d);
            g = (i * 7) % 16;
        }
        g *= 4;
        f = f + a + K[i] + (chunk[g + 3] << 24) + (chunk[g + 2] << 16) + (chunk[g + 1] << 8) + chunk[g];
        a = d;
        d = c;
        c = b;
        b += (f << S[i]) | (f >> (32 - S[i]));
    }
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
}

void        hash_md5(uint8_t *msg, uint8_t *hashed, uint32_t size)
{
    uint32_t nb_chunk = (size / 64) + 1 + ((size % 64) >= 56 ? 1 : 0);
    uint8_t chunk[nb_chunk * 64];

    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
    preprocessing(msg, chunk);

    for (uint32_t i = 0; i < nb_chunk; ++i) {
        hash_chunk(&chunk[i * 64]);
    }

    memcpy(&hashed[0], &h0, sizeof(h0));
    memcpy(&hashed[4], &h1, sizeof(h1));
    memcpy(&hashed[8], &h2, sizeof(h2));
    memcpy(&hashed[12], &h3, sizeof(h3));
}