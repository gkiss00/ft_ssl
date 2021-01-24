#include "./../include/ft_ssl.h"

static void     follow3(t_md5 *tmp){
    tmp->k[60] = 0xf7537e82;
    tmp->k[61] = 0xbd3af235;
    tmp->k[62] = 0x2ad7d2bb;
    tmp->k[63] = 0xeb86d391;
}

static void     follow2(t_md5 *tmp){
    tmp->k[40] = 0x289b7ec6;
    tmp->k[41] = 0xeaa127fa;
    tmp->k[42] = 0xd4ef3085;
    tmp->k[43] = 0x04881d05;
    tmp->k[44] = 0xd9d4d039;
    tmp->k[45] = 0xe6db99e5;
    tmp->k[46] = 0x1fa27cf8;
    tmp->k[47] = 0xc4ac5665;
    tmp->k[48] = 0xf4292244;
    tmp->k[49] = 0x432aff97;
    tmp->k[50] = 0xab9423a7;
    tmp->k[51] = 0xfc93a039;
    tmp->k[52] = 0x655b59c3;
    tmp->k[53] = 0x8f0ccc92;
    tmp->k[54] = 0xffeff47d;
    tmp->k[55] = 0x85845dd1;
    tmp->k[56] = 0x6fa87e4f;
    tmp->k[57] = 0xfe2ce6e0;
    tmp->k[58] = 0xa3014314;
    tmp->k[59] = 0x4e0811a1;
    follow3(tmp);
}

static void     follow1(t_md5 *tmp){
    tmp->k[20] = 0xd62f105d;
    tmp->k[21] = 0x02441453;
    tmp->k[22] = 0xd8a1e681;
    tmp->k[23] = 0xe7d3fbc8;
    tmp->k[24] = 0x21e1cde6;
    tmp->k[25] = 0xc33707d6;
    tmp->k[26] = 0xf4d50d87;
    tmp->k[27] = 0x455a14ed;
    tmp->k[28] = 0xa9e3e905;
    tmp->k[29] = 0xfcefa3f8;
    tmp->k[30] = 0x676f02d9;
    tmp->k[31] = 0x8d2a4c8a;
    tmp->k[32] = 0xfffa3942;
    tmp->k[33] = 0x8771f681;
    tmp->k[34] = 0x6d9d6122;
    tmp->k[35] = 0xfde5380c;
    tmp->k[36] = 0xa4beea44;
    tmp->k[37] = 0x4bdecfa9;
    tmp->k[38] = 0xf6bb4b60;
    tmp->k[39] = 0xbebfbc70;
    follow2(tmp);
}

void            fill_k(t_md5 *tmp)
{
    tmp->k[0] = 0xd76aa478;
    tmp->k[1] = 0xe8c7b756;
    tmp->k[2] = 0x242070db;
    tmp->k[3] = 0xc1bdceee;
    tmp->k[4] = 0xf57c0faf;
    tmp->k[5] = 0x4787c62a;
    tmp->k[6] = 0xa8304613;
    tmp->k[7] = 0xfd469501;
    tmp->k[8] = 0x698098d8;
    tmp->k[9] = 0x8b44f7af;
    tmp->k[10] = 0xffff5bb1;
    tmp->k[11] = 0x895cd7be;
    tmp->k[12] = 0x6b901122;
    tmp->k[13] = 0xfd987193;
    tmp->k[14] = 0xa679438e;
    tmp->k[15] = 0x49b40821;
    tmp->k[16] = 0xf61e2562;
    tmp->k[17] = 0xc040b340;
    tmp->k[18] = 0x265e5a51;
    tmp->k[19] = 0xe9b6c7aa;
    follow1(tmp);
}