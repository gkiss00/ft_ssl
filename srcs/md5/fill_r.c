#include "./../include/ft_ssl.h"

static void follow3(t_md5 *tmp)
{
    tmp->r[60] = 6;
    tmp->r[61] = 10;
    tmp->r[62] = 15;
    tmp->r[63] = 21;
}

static void follow2(t_md5 *tmp)
{
    tmp->r[40] = 4;
    tmp->r[41] = 11;
    tmp->r[42] = 16;
    tmp->r[43] = 23;
    tmp->r[44] = 4;
    tmp->r[45] = 11;
    tmp->r[46] = 16;
    tmp->r[47] = 23;
    tmp->r[48] = 6;
    tmp->r[49] = 10;
    tmp->r[50] = 15;
    tmp->r[51] = 21;
    tmp->r[52] = 6;
    tmp->r[53] = 10;
    tmp->r[54] = 15;
    tmp->r[55] = 21;
    tmp->r[56] = 6;
    tmp->r[57] = 10;
    tmp->r[58] = 15;
    tmp->r[59] = 21;
    follow3(tmp);
}

static void follow1(t_md5 *tmp)
{
    tmp->r[20] = 5;
    tmp->r[21] = 9;
    tmp->r[22] = 14;
    tmp->r[23] = 20;
    tmp->r[24] = 5;
    tmp->r[25] = 9;
    tmp->r[26] = 14;
    tmp->r[27] = 20;
    tmp->r[28] = 5;
    tmp->r[29] = 9;
    tmp->r[30] = 14;
    tmp->r[31] = 20;
    tmp->r[32] = 4;
    tmp->r[33] = 11;
    tmp->r[34] = 16;
    tmp->r[35] = 23;
    tmp->r[36] = 4;
    tmp->r[37] = 11;
    tmp->r[38] = 16;
    tmp->r[39] = 23;
    follow2(tmp);
}

void        fill_r(t_md5 *tmp)
{
    tmp->r[0] = 7;
    tmp->r[1] = 12;
    tmp->r[2] = 17;
    tmp->r[3] = 22;
    tmp->r[4] = 7;
    tmp->r[5] = 12;
    tmp->r[6] = 17;
    tmp->r[7] = 22;
    tmp->r[8] = 7;
    tmp->r[9] = 12;
    tmp->r[10] = 17;
    tmp->r[11] = 22;
    tmp->r[12] = 7;
    tmp->r[13] = 12;
    tmp->r[14] = 17;
    tmp->r[15] = 22;
    tmp->r[16] = 5;
    tmp->r[17] = 9;
    tmp->r[18] = 14;
    tmp->r[19] = 20;
    follow1(tmp);
}